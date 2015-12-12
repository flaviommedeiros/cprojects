#ifdef CONFIG_SYN_COOKIES
if (sysctl_tcp_syncookies) {
		msg = "Sending cookies";
		want_cookie = 1;
		NET_INC_STATS_BH(sock_net(sk), LINUX_MIB_TCPREQQFULLDOCOOKIES);
	} else
#endif
		NET_INC_STATS_BH(sock_net(sk), LINUX_MIB_TCPREQQFULLDROP);
