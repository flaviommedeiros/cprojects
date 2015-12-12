#ifdef CONFIG_CONCURRENT_MODE
if (padapter->iface_type == IFACE_PORT1)
		reg_bcn_ctl = REG_BCN_CTRL_1;
	else
#endif
		reg_bcn_ctl = REG_BCN_CTRL;
