#ifdef SUPPORT_SD_LOCK
if (ptr[1] & 0x7D)
#else
			if (ptr[1] & 0x7F)
#endif
			{
				RTSX_DEBUGP("ptr[1]: 0x%02x\n", ptr[1]);
				TRACE_RET(chip, STATUS_FAIL);
			}
