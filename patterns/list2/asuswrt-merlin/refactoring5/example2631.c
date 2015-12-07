#ifdef RTCONFIG_USB_BECEEM
if(is_gct_dongle(0, vid, pid)){
		if(strcmp(nvram_safe_get("stop_cd_remove"), "1")){
			usb_dbg("(%s): Running gctwimax -D...\n", device_name);
			xstart("gctwimax", "-D");
		}
	}
	else
#endif
	if(is_storage_cd(0, vid, pid)){
		usb_dbg("(%s): skip to eject CD...\n", device_name);
	}
	else if(strcmp(nvram_safe_get("stop_cd_remove"), "1")){
		usb_dbg("(%s): Running sdparm...\n", device_name);

		snprintf(eject_cmd, 128, "/dev/%s", device_name);
		eval("sdparm", "--command=eject", eject_cmd);
		sleep(1);

		if(find_sg_of_device(device_name, sg_device, sizeof(sg_device)) != NULL){
			snprintf(eject_cmd, 128, "/dev/%s", sg_device);
			eval("sdparm", "--command=eject", eject_cmd);
			sleep(1);
		}

		modprobe_r("sr_mod");
		modprobe_r("cdrom");
	}
