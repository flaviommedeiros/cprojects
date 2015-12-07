#ifdef TCP_FD_CACHE
if (cfg_get(tcp, tcp_cfg, fd_cache)) {
					tcp_fd_cache_add(c, fd);
				} else
#endif /* TCP_FD_CACHE */
					tcp_safe_close(fd);
