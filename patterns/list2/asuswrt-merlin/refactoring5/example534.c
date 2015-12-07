#ifdef RTCONFIG_WEBDAV_PENDING
if(strcmp(protocol, "webdav")==0) {
		if(notify_rc_for_nas("restart_webdav") != 0) {
			insert_hook_func(wp, fn, "alert_msg.Action1");
			return -1;
		}
	}
	else
#endif
	if (notify_rc_for_nas("restart_ftpsamba") != 0){
		insert_hook_func(wp, fn, "alert_msg.Action1");
		return -1;
	}
