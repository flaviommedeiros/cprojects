#ifdef HAVE_IPV6
if (server->addr.sa.sa_family == AF_INET6)
			{
			  if (new->rfd6 || (new->rfd6 = allocate_rfd(AF_INET6)))
			    fd = new->rfd6->fd;
			}
		      else
#endif
			{
			  if (new->rfd4 || (new->rfd4 = allocate_rfd(AF_INET)))
			    fd = new->rfd4->fd;
			}
