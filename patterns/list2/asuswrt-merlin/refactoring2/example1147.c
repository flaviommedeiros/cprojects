#ifndef CONFIG_CYZ_INTR
if (!IS_CYC_Z(*cinfo))
#endif
		cy_writew(cinfo->ctl_addr + 0x68,
				readw(cinfo->ctl_addr + 0x68) & ~0x0900);
