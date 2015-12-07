if (!nvram_match("nf_ftp", "0")
#ifdef RTCONFIG_FTP
		|| nvram_match("ftp_enable", "1")	// !!TB - FTP Server
#endif
		) {
		ct_modprobe("ftp");
	}
	else {
		ct_modprobe_r("ftp");
	}
