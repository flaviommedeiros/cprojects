#ifdef CONFIG_SYN_COOKIES
if (sysctl_tcp_syncookies)
			want_cookie = 1;
		else
#endif
		goto drop;
