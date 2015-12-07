if (strcmp(protocol, "cifs") && strcmp(protocol, "ftp") && strcmp(protocol, "dms")
#ifdef RTCONFIG_WEBDAV_PENDING
&& strcmp(protocol, "webdav")
#endif
){
		insert_hook_func(wp, fn, "alert_msg.Input2");
		return -1;
	}
