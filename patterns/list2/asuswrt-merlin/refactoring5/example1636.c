#ifdef BCM_MMC
if(isMMCDevice(device_name))
				len = strlen(DEFAULT_MMC_TAG);
			else
#endif
				len = strlen(DEFAULT_USB_TAG);
