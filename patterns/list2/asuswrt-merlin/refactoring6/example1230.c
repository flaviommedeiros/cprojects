if (is_firsttime()
#ifdef RTCONFIG_FINDASUS
		    && !isDeviceDiscovery
#endif
		   )
			//file = "QIS_wizard.htm";
			file = "QIS_default.cgi";
#ifdef RTCONFIG_FINDASUS
		else if(isDeviceDiscovery == 1)
			file = "find_device.asp";
#endif
		else
			file = "index.asp";
