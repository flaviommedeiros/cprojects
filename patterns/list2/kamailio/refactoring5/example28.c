#ifdef TCP_FD_CACHE
if (unlikely(fd_cache_e)){
				tcp_fd_cache_rm(fd_cache_e);
				fd_cache_e = 0;
				tcp_safe_close(fd);
			}else
#endif /* TCP_FD_CACHE */
				if (do_close_fd) tcp_safe_close(fd);
