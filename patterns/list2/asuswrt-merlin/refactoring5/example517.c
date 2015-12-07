#ifdef RTCONFIG_QTN
if (unit)
			ret += wl_status_5g_array(eid, wp, argc, argv);
		else
#endif
			ret += wl_status_array(eid, wp, argc, argv, unit);
