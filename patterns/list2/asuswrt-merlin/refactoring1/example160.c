if (add_account(account, password) < 0){
		insert_hook_func(wp, fn, "alert_msg.Action2");
		return -1;
	}
#ifdef RTCONFIG_WEBDAV_PENDING
	else if(add_webdav_account(account) < 0) {
		insert_hook_func(wp, fn, "alert_msg.Action2");
		return -1;
	}
#endif
