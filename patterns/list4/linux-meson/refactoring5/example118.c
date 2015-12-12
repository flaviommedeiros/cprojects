#ifdef RTK_DMP_PLATFORM
if(sz > 0x4000)
		pbuf = (u8 *)dvr_malloc(sz);
	else
#endif		
		pbuf = kmalloc(sz,in_interrupt() ? GFP_ATOMIC : GFP_KERNEL);
