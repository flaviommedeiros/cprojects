#ifdef RTCONFIG_HTTPS
if(do_ssl)
		ret = fcntl(ssl_stream_fd , F_GETOWN, 0);
	else
#endif
	ret = fcntl(fileno(stream), F_GETOWN, 0);
