#ifdef SUPPORT_MSXC
if ((buf[cur_addr_off + 8] == 0x10) || (buf[cur_addr_off + 8] == 0x13))
#else
		if (buf[cur_addr_off + 8] == 0x10)
#endif
		{
			sys_info_addr = ((u32)buf[cur_addr_off + 0] << 24) |
				((u32)buf[cur_addr_off + 1] << 16) |
				((u32)buf[cur_addr_off + 2] << 8) | buf[cur_addr_off + 3];
			sys_info_size = ((u32)buf[cur_addr_off + 4] << 24) |
				((u32)buf[cur_addr_off + 5] << 16) |
				((u32)buf[cur_addr_off + 6] << 8) | buf[cur_addr_off + 7];
			RTSX_DEBUGP("sys_info_addr = 0x%x, sys_info_size = 0x%x\n",
					sys_info_addr, sys_info_size);
			if (sys_info_size != 96)  {
				kfree(buf);
				TRACE_RET(chip, STATUS_FAIL);
			}
			if (sys_info_addr < 0x1A0) {
				kfree(buf);
				TRACE_RET(chip, STATUS_FAIL);
			}
			if ((sys_info_size + sys_info_addr) > 0x8000) {
				kfree(buf);
				TRACE_RET(chip, STATUS_FAIL);
			}

#ifdef SUPPORT_MSXC
			if (buf[cur_addr_off + 8] == 0x13) {
				ms_card->ms_type |= MS_XC;
			}
#endif
#ifdef SUPPORT_PCGL_1P18
			found_sys_info = 1;
#else
			break;
#endif
		}
