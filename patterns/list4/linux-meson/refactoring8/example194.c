const struct rtw_proc_hdl drv_proc_hdls [] = {
	{"ver_info", proc_get_drv_version, NULL},
	{"log_level", proc_get_log_level, proc_set_log_level},
#ifdef DBG_MEM_ALLOC
	{"mstat", proc_get_mstat, NULL},
#endif /* DBG_MEM_ALLOC */
};
