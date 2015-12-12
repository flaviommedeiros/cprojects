return sys_fanotify_mark(fanotify_fd, flags,
#ifdef __BIG_ENDIAN
				((__u64)mask0 << 32) | mask1,
#else
				((__u64)mask1 << 32) | mask0,
#endif
				 dfd, pathname);
