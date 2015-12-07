if (del_account(account) < 0){
		insert_hook_func(wp, fn, "alert_msg.Action3");
		return -1;
	}
#ifdef RTCONFIG_WEBDAV_PENDING
	else if(del_webdav_account(account)<0) {
		insert_hook_func(wp, fn, "alert_msg.Action3");
		return -1;
	}
#endif
