#ifdef RTCONFIG_AP_CARRIER_DETECTION
if(nvram_match("JP_CS","1"))
#else	
	if (nvram_match(strcat_r(prefix, "country_code", tmp), "JP"))
#endif	   
	{
		fprintf(fp, "RDRegion=%s\n", "JAP");
		fprintf(fp, "CarrierDetect=%d\n", 1);
	}
	else
#endif
	{
#ifdef RTCONFIG_RALINK_DFS		
		fprintf(fp, "RDRegion=%s\n",nvram_get("reg_spec"));
#else		
		fprintf(fp, "RDRegion=\n");
#endif		
		fprintf(fp, "CarrierDetect=%d\n", 0);
	}
