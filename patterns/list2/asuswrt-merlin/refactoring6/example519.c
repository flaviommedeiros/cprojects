if (!strcmp(status, "Failed") 
#ifdef RTCONFIG_WPS_ENROLLEE
				|| !strcmp(status, "INACTIVE")
#endif
		) {
			dbG("\nWPS %s\n", status);
			ret = 1;
		}
		else
			ret = 0;
