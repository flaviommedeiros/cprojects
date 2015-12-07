#ifdef RTCONFIG_HTTPS
if (!do_ssl)
#endif
				shutdown(item->fd, 2), item->fd = -1;
