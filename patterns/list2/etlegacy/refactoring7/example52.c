return(va("%d-%02d-%02d-%02d%02d%02d-%s%s",
	          1900 + ct.tm_year, ct.tm_mon + 1, ct.tm_mday,
	          ct.tm_hour, ct.tm_min, ct.tm_sec,
	          Info_ValueForKey(pszServerInfo, "mapname"),
#ifdef FEATURE_MULTIVIEW
	          (cg.mvTotalClients < 1) ?
#endif
	          ""
#ifdef FEATURE_MULTIVIEW
			  : "-MVD"
#endif
	          ));
