#ifdef CONFIG_SYN_COOKIES
if (sysctl_tcp_syncookies)
		msg = "Sending cookies";
	else
#endif
		msg = "Dropping request";
