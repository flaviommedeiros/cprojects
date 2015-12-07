#ifndef CONFIG_CYZ_INTR
if (!cy_is_Z(cinfo))
#endif
		cy_writew(&cinfo->ctl_addr.p9060->intr_ctrl_stat,
			readw(&cinfo->ctl_addr.p9060->intr_ctrl_stat) &
			~0x0900);
