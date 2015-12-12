#ifdef AMLOGIC_CHIP_SUPPORT
if((unsigned long)data_buf == 0x3400000)
		{
			for(j=0; j<ATA_DRQ_BLK_LENGTH_BYTE; j++)
			{
				WRITE_BYTE_TO_FIFO(*byte_buf++);
			}
		}
		else
#endif
		{
			memcpy(data_buf, byte_buf, ATA_DRQ_BLK_LENGTH_BYTE);
			data_buf += ATA_DRQ_BLK_LENGTH_BYTE;
		}
