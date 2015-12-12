#ifdef AMLOGIC_CHIP_SUPPORT
if((unsigned)data_buf == 0x3400000)
					{
						WRITE_BYTE_TO_FIFO(temp);
					}
					else
#endif
					{
						*data_buf = temp;
						data_buf++;
					}
