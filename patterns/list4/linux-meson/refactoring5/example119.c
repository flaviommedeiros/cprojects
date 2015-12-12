#ifdef RTK_DMP_PLATFORM
if(sz > 0x4000)
		dvr_free(pbuf);
	else
#endif
		kfree(pbuf);
