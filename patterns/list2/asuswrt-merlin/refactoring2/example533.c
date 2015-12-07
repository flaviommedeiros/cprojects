#ifdef RTCONFIG_WIRELESSREPEATER
if ((fp = fopen("/etc/dnsmasq.conf", "w")) == NULL)
		return;
