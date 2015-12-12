#ifdef CONFIG_CONCURRENT_MODE
if (padapter->iface_type == IFACE_PORT1)
	{
		bcn_ctrl_reg = REG_BCN_CTRL_1;
	}
	else
#endif
	{
		bcn_ctrl_reg = REG_BCN_CTRL;
	}
