static struct iw_priv_args wl_iw_priv_args[] = {
	{
		WL_IW_SET_LEDDC,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
		0,
		"set_leddc"
	},
	{
		WL_IW_SET_VLANMODE,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
		0,
		"set_vlanmode"
	},
	{
		WL_IW_SET_PM,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
		0,
		"set_pm"
	},
#if WIRELESS_EXT > 17
#endif /* WIRELESS_EXT > 17 */
	{ 0, 0, 0, { 0 } }
};
