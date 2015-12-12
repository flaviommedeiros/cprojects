#ifdef SUPPORT_SD_LOCK
if (ptr[1] & 0x7D)
#else
		if (ptr[1] & 0x7F)
#endif
		{
			TRACE_RET(chip, STATUS_FAIL);
		}
