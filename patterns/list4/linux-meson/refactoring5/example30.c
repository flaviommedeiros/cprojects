#ifdef AMLOGIC_CHIP_SUPPORT
if((unsigned long)data_buf == 0x3400000)
		{
			for(int i=0; i<read_cnt; i++)
			{
				WRITE_BYTE_TO_FIFO(xd_sm_buf->page_buf[i]);
				xd_sm_delay_100ns(1);
			}
		}
		else
		#endif
		{
			memcpy(data_buf+data_offset, xd_sm_buf->page_buf, read_cnt);
		}
