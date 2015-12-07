#ifdef TCP_FD_CACHE
if (unlikely((fd_cache_e==0) && use_fd_cache)){
		tcp_fd_cache_add(c, fd);
	}else
#endif /* TCP_FD_CACHE */
	if (do_close_fd) {
		if (unlikely(tcp_safe_close(fd) < 0))
			LM_ERR("closing temporary send fd for %p: %s: "
					"close(%d) failed (flags 0x%x): %s (%d)\n", c,
					su2a(&c->rcv.src_su, sizeof(c->rcv.src_su)),
					fd, c->flags, strerror(errno), errno);
	}
