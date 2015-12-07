#ifdef RTCONFIG_USB_BECEEM
if(is_beceem_dongle(1, vid, pid)){
		usb_dbg("(%s): Runing Beceem module...\n", device_name);

		char *isp = nvram_safe_get("modem_isp");

		eval("rm", "-rf", BECEEM_DIR);
		eval("mkdir", "-p", BECEEM_DIR);
		eval("ln", "-sf", "/rom/Beceem_firmware/RemoteProxy.cfg", "/tmp/Beceem_firmware/RemoteProxy.cfg");

		if(!strcmp(isp, "Yota")){
			eval("ln", "-sf", "/rom/Beceem_firmware/macxvi200.bin.normal", "/tmp/Beceem_firmware/macxvi200.bin");
			eval("ln", "-sf", "/rom/Beceem_firmware/macxvi.cfg.yota", "/tmp/Beceem_firmware/macxvi.cfg");
			eval("ln", "-sf", "/rom/Beceem_firmware/Server_CA.pem.yota", "/tmp/Beceem_firmware/Server_CA.pem");
		}
		else if(!strcmp(isp, "GMC")){
			eval("ln", "-sf", "/rom/Beceem_firmware/macxvi200.bin.normal", "/tmp/Beceem_firmware/macxvi200.bin");
			eval("ln", "-sf", "/rom/Beceem_firmware/macxvi.cfg.gmc", "/tmp/Beceem_firmware/macxvi.cfg");
		}
		else if(!strcmp(isp, "FreshTel")){
			eval("ln", "-sf", "/rom/Beceem_firmware/macxvi200.bin.normal", "/tmp/Beceem_firmware/macxvi200.bin");
			eval("ln", "-sf", "/rom/Beceem_firmware/macxvi.cfg.freshtel", "/tmp/Beceem_firmware/macxvi.cfg");
		}
		else if(!strcmp(isp, "Giraffe")){
			eval("ln", "-sf", "/rom/Beceem_firmware/macxvi200.bin.giraffe", "/tmp/Beceem_firmware/macxvi200.bin");
			eval("ln", "-sf", "/rom/Beceem_firmware/macxvi.cfg.giraffe", "/tmp/Beceem_firmware/macxvi.cfg");
		}
		else{
			usb_dbg("(%s): Didn't assign the ISP or it was not supported.\n", device_name);
			file_unlock(isLock);
			return 0;
		}

		//sleep(2); // sometimes the device is not ready.
		modprobe("drxvi314");
		sleep(1);

		retry = 0;
		while(!check_if_dir_exist("/sys/class/usb/usbbcm") && (retry++ < 3)){
			usb_dbg("(%s): wait %d second for binding...\n", device_name, retry);
			modprobe_r("drxvi314");

			modprobe("drxvi314");
			sleep(1);
		}
	}
	else if(is_samsung_dongle(1, vid, pid)){ // Samsung U200
		// need to run one time and fillfull the nvram: usb_path%d_act.
		usb_dbg("(%s): Runing madwimax...\n", device_name);

		nvram_set(strcat_r(prefix, "_act", tmp), "wimax0");
		nvram_set("usb_modem_act_path", usb_node);
		snprintf(buf, 128, "%u",  vid);
		nvram_set("usb_modem_act_vid", buf);
		snprintf(buf, 128, "%u",  pid);
		nvram_set("usb_modem_act_pid", buf);
	}
	else if(is_gct_dongle(1, vid, pid)){
		// need to run one time and fillfull the nvram: usb_path%d_act.
		usb_dbg("(%s): Runing GCT dongle...\n", device_name);

		nvram_set(strcat_r(prefix, "_act", tmp), "wimax0");
		nvram_set("usb_modem_act_path", usb_node);
		snprintf(buf, 128, "%u",  vid);
		nvram_set("usb_modem_act_vid", buf);
		snprintf(buf, 128, "%u",  pid);
		nvram_set("usb_modem_act_pid", buf);
	}
	else
#endif
	if(is_android_phone(0, vid, pid)){
		usb_dbg("(%s): do nothing with the MTP mode.\n", device_name);
	}
	else if(isRNDISInterface(device_name, vid, pid)){
		usb_dbg("(%s): Runing RNDIS...\n", device_name);
	}
	else if(isCDCETHInterface(device_name)){
		usb_dbg("(%s): Runing cdc_ether...\n", device_name);
	}
	else if(isNCMInterface(device_name)){
		usb_dbg("(%s): Runing cdc_ncm...\n", device_name);
	}
	else if(!strcmp(nvram_safe_get("stop_ui_insmod"), "1")){
		usb_dbg("(%s): Don't insmod the serial modules.\n", device_name);
	}
	else if(isSerialInterface(device_name, 1, vid, pid) && vid == 0x05c6 && pid == 0x9026 && nvram_get_int("usb_gobi") == 1){
		usb_dbg("(%s): Runing Gobi ...\n", device_name);
	}
	else if(!(vid == 0x05c6 && pid == 0x9026) &&
			(!strncmp(nvram_safe_get(strcat_r(prefix, "_manufacturer", tmp)), "Android", 7) || !strncmp(nvram_safe_get(strcat_r(prefix, "_product", tmp)), "Android", 7))
			){
		usb_dbg("(%s): Android phone: Runing RNDIS...\n", device_name);
	}
	else if(isSerialInterface(device_name, 1, vid, pid)){
		usb_dbg("(%s): Runing USB serial with (0x%04x/0x%04x)...\n", device_name, vid, pid);
		sleep(1);
		modprobe("usbserial");
#if LINUX_KERNEL_VERSION >= KERNEL_VERSION(2,6,36)
		modprobe("usb_wwan");
#endif
		snprintf(modem_cmd, 128, "vendor=0x%04x", vid);
		snprintf(buf, 128, "product=0x%04x", pid);
		eval("insmod", "option", modem_cmd, buf);
		sleep(1);
	}
	else if(isACMInterface(device_name, 1, vid, pid)){
		usb_dbg("(%s): Runing USB ACM...\n", device_name);
		modprobe("cdc-acm");
		sleep(1);
	}
