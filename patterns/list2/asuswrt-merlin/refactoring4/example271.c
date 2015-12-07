#if defined(__lynx__)  || defined(__sun__) || defined(__NTVIS__)
if( p && setsockopt(fd, p->p_proto, TCP_NODELAY, 
				                    (char *) &one, sizeof(one)) < 0)
#else 
				if( p && setsockopt(fd, p->p_proto, TCP_NODELAY, 
				                    &one, sizeof(one)) < 0)
#endif /* __lynx__  __sun__ __NTVIS__ */
					sockets_err("setsockopt: nodelay");
