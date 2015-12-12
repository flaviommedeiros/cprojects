static iw_handler r8192_private_handler[] = {
//	r8192_wx_set_monitor,  /* SIOCIWFIRSTPRIV */
	r8192_wx_set_crcmon,   /*SIOCIWSECONDPRIV*/
//	r8192_wx_set_forceassociate,
//	r8192_wx_set_beaconinterval,
//	r8192_wx_set_monitor_type,
	r8192_wx_set_scan_type,
	r8192_wx_set_rawtx,
#ifdef JOHN_IOCTL
	r8192_wx_read_regs,
	r8192_wx_write_regs,
	r8192_wx_read_bb,
	r8192_wx_write_bb,
        r8192_wx_read_nicb,
        r8192_wx_write_nicb,
	r8192_wx_get_ap_status,
#endif
	r8192_wx_force_reset,
        (iw_handler)NULL,
        (iw_handler)r8191su_wx_get_firm_version,
};
