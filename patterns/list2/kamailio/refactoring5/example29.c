#ifdef TCP_FD_CACHE
if (unlikely((fd_cache_e==0) && use_fd_cache)){
				tcp_fd_cache_add(c, fd);
			}else
#endif /* TCP_FD_CACHE */
				if (do_close_fd) tcp_safe_close(fd);
