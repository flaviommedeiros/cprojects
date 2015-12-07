#ifdef BCM_MMC
if(isMMCDevice(device_name)){
		if(strchr(device_name, 'p'))
			return 0;
	}
	else
#endif
	if(isdigit(device_name[strlen(device_name)-1]))
		return 0;
