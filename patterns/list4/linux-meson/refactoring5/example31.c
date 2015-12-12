#ifdef AMLOGIC_CHIP_SUPPORT
if((unsigned long)tpc_packet->param.in.buffer == 0x3400000)
		{
			for(i=0; i<tpc_packet->param.in.count; i++)
			{
				WRITE_BYTE_TO_FIFO(data_buf[i]);
			}
		}
		else
#endif
		{
			dmac_map_area(ms_mspro_info->data_buf, tpc_packet->param.in.count, 2);
			memcpy(tpc_packet->param.in.buffer, ms_mspro_info->data_buf, tpc_packet->param.in.count);
			dmac_map_area(ms_mspro_info->data_buf, tpc_packet->param.in.count, 2);	
		}
