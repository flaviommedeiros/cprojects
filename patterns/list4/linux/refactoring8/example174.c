static const struct mega_proc_file mega_proc_files[] = {
	{ "config",	      offsetof(adapter_t, proc_read), proc_show_config },
	{ "stat",	      offsetof(adapter_t, proc_stat), proc_show_stat },
	{ "mailbox",	      offsetof(adapter_t, proc_mbox), proc_show_mbox },
#if MEGA_HAVE_ENH_PROC
	{ "rebuild-rate",     offsetof(adapter_t, proc_rr), proc_show_rebuild_rate },
	{ "battery-status",   offsetof(adapter_t, proc_battery), proc_show_battery },
	{ "diskdrives-ch0",   offsetof(adapter_t, proc_pdrvstat[0]), proc_show_pdrv_ch0 },
	{ "diskdrives-ch1",   offsetof(adapter_t, proc_pdrvstat[1]), proc_show_pdrv_ch1 },
	{ "diskdrives-ch2",   offsetof(adapter_t, proc_pdrvstat[2]), proc_show_pdrv_ch2 },
	{ "diskdrives-ch3",   offsetof(adapter_t, proc_pdrvstat[3]), proc_show_pdrv_ch3 },
	{ "raiddrives-0-9",   offsetof(adapter_t, proc_rdrvstat[0]), proc_show_rdrv_10 },
	{ "raiddrives-10-19", offsetof(adapter_t, proc_rdrvstat[1]), proc_show_rdrv_20 },
	{ "raiddrives-20-29", offsetof(adapter_t, proc_rdrvstat[2]), proc_show_rdrv_30 },
	{ "raiddrives-30-39", offsetof(adapter_t, proc_rdrvstat[3]), proc_show_rdrv_40 },
#endif
	{ NULL }
};
