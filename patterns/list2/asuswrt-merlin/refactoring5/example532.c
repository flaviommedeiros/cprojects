#ifdef RTCONFIG_HTTPS
if(do_ssl)
				shutdown(ssl_stream_fd, SHUT_RDWR);
			else
#endif
				shutdown(fileno(stream), SHUT_RDWR);
