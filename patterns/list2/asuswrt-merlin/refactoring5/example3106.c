#ifdef BCM_MMC
if(isMMCDevice(device_name)){ // SD card.
		snprintf(buf, buf_size, "%s", SDCARD_PORT);
	}
	else
#endif
	if(get_usb_port_by_string(usb_path, buf, buf_size) == NULL){
		usb_dbg("(%s): Fail to get usb port: %s.\n", device_name, usb_path);
		return NULL;
	}
