#ifdef BCM_MMC
if(isMMCDevice(device_name))
				strcpy(follow_disk_info->tag, DEFAULT_MMC_TAG);
			else
#endif
				strcpy(follow_disk_info->tag, DEFAULT_USB_TAG);
