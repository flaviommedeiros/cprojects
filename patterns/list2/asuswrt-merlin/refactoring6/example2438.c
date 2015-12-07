if(!isSerialInterface(device_name, 1, vid, pid)
			&& !isACMInterface(device_name, 1, vid, pid)
			&& !isRNDISInterface(device_name, vid, pid)
			&& !isCDCETHInterface(device_name)
			&& !isNCMInterface(device_name)
#ifdef RTCONFIG_USB_BECEEM
			&& !isGCTInterface(device_name)
#endif
			){
		usb_dbg("(%s): Not modem interface.\n", device_name);
		file_unlock(isLock);
		return 0;
	}
