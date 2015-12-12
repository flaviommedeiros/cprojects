VOID RTMPIoctlMAC(
	IN	PRTMP_ADAPTER	pAdapter,
	IN	struct iwreq	*wrq)
{
	PSTRING				this_char;
	PSTRING				value;
	INT					j = 0, k = 0;
	STRING				msg[1024];
	STRING				arg[255];
	ULONG				macAddr = 0;
	UCHAR				temp[16];
	STRING				temp2[16];
	UINT32				macValue = 0;
	INT					Status;
	BOOLEAN				bIsPrintAllMAC = FALSE;


	memset(msg, 0x00, 1024);
	if (wrq->u.data.length > 1) //No parameters.
	{
	    Status = copy_from_user(arg, wrq->u.data.pointer, (wrq->u.data.length > 255) ? 255 : wrq->u.data.length);
		sprintf(msg, "\n");

		//Parsing Read or Write
	    this_char = arg;
		if (!*this_char)
			goto next;

		if ((value = rtstrchr(this_char, '=')) != NULL)
			*value++ = 0;

		if (!value || !*value)
		{ //Read
			// Sanity check
			if(strlen(this_char) > 4)
				goto next;

			j = strlen(this_char);
			while(j-- > 0)
			{
				if(this_char[j] > 'f' || this_char[j] < '0')
					return;
			}

			// Mac Addr
			k = j = strlen(this_char);
			while(j-- > 0)
			{
				this_char[4-k+j] = this_char[j];
			}

			while(k < 4)
				this_char[3-k++]='0';
			this_char[4]='\0';

			if(strlen(this_char) == 4)
			{
				AtoH(this_char, temp, 2);
				macAddr = *temp*256 + temp[1];
				if (macAddr < 0xFFFF)
				{
					RTMP_IO_READ32(pAdapter, macAddr, &macValue);
					DBGPRINT(RT_DEBUG_TRACE, ("MacAddr=%lx, MacValue=%x\n", macAddr, macValue));
					sprintf(msg+strlen(msg), "[0x%08lX]:%08X  ", macAddr , macValue);
				}
				else
				{//Invalid parametes, so default printk all mac
					bIsPrintAllMAC = TRUE;
					goto next;
				}
			}
		}
		else
		{ //Write
			memcpy(&temp2, value, strlen(value));
			temp2[strlen(value)] = '\0';

			// Sanity check
			if((strlen(this_char) > 4) || strlen(temp2) > 8)
				goto next;

			j = strlen(this_char);
			while(j-- > 0)
			{
				if(this_char[j] > 'f' || this_char[j] < '0')
					return;
			}

			j = strlen(temp2);
			while(j-- > 0)
			{
				if(temp2[j] > 'f' || temp2[j] < '0')
					return;
			}

			//MAC Addr
			k = j = strlen(this_char);
			while(j-- > 0)
			{
				this_char[4-k+j] = this_char[j];
			}

			while(k < 4)
				this_char[3-k++]='0';
			this_char[4]='\0';

			//MAC value
			k = j = strlen(temp2);
			while(j-- > 0)
			{
				temp2[8-k+j] = temp2[j];
			}

			while(k < 8)
				temp2[7-k++]='0';
			temp2[8]='\0';

			{
				AtoH(this_char, temp, 2);
				macAddr = *temp*256 + temp[1];

				AtoH(temp2, temp, 4);
				macValue = *temp*256*256*256 + temp[1]*256*256 + temp[2]*256 + temp[3];

				// debug mode
				if (macAddr == (HW_DEBUG_SETTING_BASE + 4))
				{
					// 0x2bf4: byte0 non-zero: enable R17 tuning, 0: disable R17 tuning
                    if (macValue & 0x000000ff)
                    {
                        pAdapter->BbpTuning.bEnable = TRUE;
                        DBGPRINT(RT_DEBUG_TRACE,("turn on R17 tuning\n"));
                    }
                    else
                    {
                        UCHAR R66;
                        pAdapter->BbpTuning.bEnable = FALSE;
                        R66 = 0x26 + GET_LNA_GAIN(pAdapter);
#ifdef RALINK_ATE
						if (ATE_ON(pAdapter))
						{
							ATE_BBP_IO_WRITE8_BY_REG_ID(pAdapter, BBP_R66, (0x26 + GET_LNA_GAIN(pAdapter)));
						}
						else
#endif // RALINK_ATE //

							RTMP_BBP_IO_WRITE8_BY_REG_ID(pAdapter, BBP_R66, (0x26 + GET_LNA_GAIN(pAdapter)));
                        DBGPRINT(RT_DEBUG_TRACE,("turn off R17 tuning, restore to 0x%02x\n", R66));
                    }
					return;
				}

				DBGPRINT(RT_DEBUG_TRACE, ("MacAddr=%02lx, MacValue=0x%x\n", macAddr, macValue));

				RTMP_IO_WRITE32(pAdapter, macAddr, macValue);
				sprintf(msg+strlen(msg), "[0x%08lX]:%08X  ", macAddr, macValue);
			}
		}
	}
	else
		bIsPrintAllMAC = TRUE;
next:
	if (bIsPrintAllMAC)
	{
		struct file		*file_w;
		PSTRING			fileName = "MacDump.txt";
		mm_segment_t	orig_fs;

		orig_fs = get_fs();
		set_fs(KERNEL_DS);

		// open file
		file_w = filp_open(fileName, O_WRONLY|O_CREAT, 0);
		if (IS_ERR(file_w))
		{
			DBGPRINT(RT_DEBUG_TRACE, ("-->2) %s: Error %ld opening %s\n", __FUNCTION__, -PTR_ERR(file_w), fileName));
		}
		else
		{
			if (file_w->f_op && file_w->f_op->write)
			{
				file_w->f_pos = 0;
				macAddr = 0x1000;

				while (macAddr <= 0x1800)
				{
					RTMP_IO_READ32(pAdapter, macAddr, &macValue);
					sprintf(msg, "%08lx = %08X\n", macAddr, macValue);

					// write data to file
					file_w->f_op->write(file_w, msg, strlen(msg), &file_w->f_pos);

					printk("%s", msg);
					macAddr += 4;
				}
				sprintf(msg, "\nDump all MAC values to %s\n", fileName);
			}
			filp_close(file_w, NULL);
		}
		set_fs(orig_fs);
	}
	if(strlen(msg) == 1)
		sprintf(msg+strlen(msg), "===>Error command format!");

	// Copy the information into the user buffer
	wrq->u.data.length = strlen(msg);
	Status = copy_to_user(wrq->u.data.pointer, msg, wrq->u.data.length);

	DBGPRINT(RT_DEBUG_TRACE, ("<==RTMPIoctlMAC\n\n"));
}
