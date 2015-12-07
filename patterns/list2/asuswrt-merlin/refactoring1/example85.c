if(add_account(buf1, buf2) < 0)
#endif
	{
		insert_hook_func(wp, fn, "alert_msg.Action2");
		return -1;
	}
#ifdef RTCONFIG_WEBDAV_PENDING
	else if(add_webdav_account(nvram_safe_get("http_username"))<0) {
		insert_hook_func(wp, "init_account_error", "alert_msg.Action2");
		return -1;
	}
#endif
