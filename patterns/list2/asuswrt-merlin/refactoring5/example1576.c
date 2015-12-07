#ifdef RTCONFIG_QTN
if (unit)
			ret += wl_status_5g(eid, wp, argc, argv);
		else
#endif
		ret += wl_status(eid, wp, argc, argv, unit);
