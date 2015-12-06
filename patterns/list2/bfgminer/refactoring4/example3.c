#ifndef __linux
if (unlikely(setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (const void *)&tcp_one, sizeof(tcp_one))))
#else /* __linux */
		if (unlikely(setsockopt(fd, SOL_TCP, TCP_NODELAY, (const void *)&tcp_one, sizeof(tcp_one))))
#endif /* __linux */
			ret = 1;
