#ifdef RTCONFIG_USB_PRINTER
if(device_type == DEVICE_TYPE_PRINTER){
		sprintf(device_path, "%s/%s/device", SYS_USB, device_name);
		if(realpath(device_path, usb_path) == NULL){
			usb_dbg("(%s): Fail to get link: %s.\n", device_name, device_path);
			return NULL;
		}
	}
	else
#endif
#ifdef RTCONFIG_USB_MODEM
	if(device_type == DEVICE_TYPE_SG){
		sprintf(device_path, "%s/%s/device", SYS_SG, device_name);
		if(realpath(device_path, usb_path) == NULL){
			usb_dbg("(%s): Fail to get link: %s.\n", device_name, device_path);
			return NULL;
		}
	}
	else
	if(device_type == DEVICE_TYPE_CD){
		sprintf(device_path, "%s/%s/device", SYS_BLOCK, device_name);
		if(realpath(device_path, usb_path) == NULL){
			usb_dbg("(%s): Fail to get link: %s.\n", device_name, device_path);
			return NULL;
		}
	}
	else
	if(device_type == DEVICE_TYPE_MODEM){
		sprintf(device_path, "%s/%s/device", SYS_TTY, device_name);
		if(realpath(device_path, usb_path) == NULL){
			sleep(1); // Sometimes link would be built slowly, so try again.

			if(realpath(device_path, usb_path) == NULL){
				usb_dbg("(%s)(2/2): Fail to get link: %s.\n", device_name, device_path);
				return NULL;
			}
		}
	}
	else
#endif
#ifdef RTCONFIG_USB_BECEEM
	if(device_type == DEVICE_TYPE_BECEEM){
		sprintf(device_path, "%s/%s/device", SYS_USB, device_name);
		if(realpath(device_path, usb_path) == NULL){
			if(realpath(device_path, usb_path) == NULL){
				usb_dbg("(%s)(2/2): Fail to get link: %s.\n", device_name, device_path);
				return NULL;
			}
		}
	}
	else
#endif
		return NULL;
