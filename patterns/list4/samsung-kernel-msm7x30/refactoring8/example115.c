static iw_handler wl_iw_priv_handler[] = {
	wl_iw_set_leddc,
	wl_iw_set_vlanmode,
	wl_iw_set_pm,
#if WIRELESS_EXT > 17
#endif /* WIRELESS_EXT > 17 */
	NULL
};
