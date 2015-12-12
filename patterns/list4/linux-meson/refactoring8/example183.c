static struct iw_priv_args ipw_priv_args[] = {
	{
	 .cmd = IPW_PRIV_SET_POWER,
	 .set_args = IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
	 .name = "set_power"},
	{
	 .cmd = IPW_PRIV_GET_POWER,
	 .get_args = IW_PRIV_TYPE_CHAR | IW_PRIV_SIZE_FIXED | MAX_WX_STRING,
	 .name = "get_power"},
	{
	 .cmd = IPW_PRIV_SET_MODE,
	 .set_args = IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
	 .name = "set_mode"},
	{
	 .cmd = IPW_PRIV_GET_MODE,
	 .get_args = IW_PRIV_TYPE_CHAR | IW_PRIV_SIZE_FIXED | MAX_WX_STRING,
	 .name = "get_mode"},
	{
	 .cmd = IPW_PRIV_SET_PREAMBLE,
	 .set_args = IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
	 .name = "set_preamble"},
	{
	 .cmd = IPW_PRIV_GET_PREAMBLE,
	 .get_args = IW_PRIV_TYPE_CHAR | IW_PRIV_SIZE_FIXED | IFNAMSIZ,
	 .name = "get_preamble"},
	{
	 IPW_PRIV_RESET,
	 IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 0, 0, "reset"},
	{
	 IPW_PRIV_SW_RESET,
	 IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 0, 0, "sw_reset"},
#ifdef CONFIG_IPW2200_MONITOR
	{
	 IPW_PRIV_SET_MONITOR,
	 IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 2, 0, "monitor"},
#endif				/* CONFIG_IPW2200_MONITOR */
};
