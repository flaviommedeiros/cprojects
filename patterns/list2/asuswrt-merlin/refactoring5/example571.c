#ifdef BCM_MMC
if(isMMCDevice(device_name))
		// SD card: mmcblk0p1.
		order = (u32)strtol(device_name+8, NULL, 10);
	else
#endif
		// sda1.
		order = (u32)strtol(device_name+3, NULL, 10);
