#ifdef HAVE_IPV6
if (start->addr.sa.sa_family == AF_INET6)
		    {
		      if (!forward->rfd6 &&
			  !(forward->rfd6 = allocate_rfd(AF_INET6)))
			break;
		      daemon->rfd_save = forward->rfd6;
		      fd = forward->rfd6->fd;
		    }
		  else
#endif
		    {
		      if (!forward->rfd4 &&
			  !(forward->rfd4 = allocate_rfd(AF_INET)))
			break;
		      daemon->rfd_save = forward->rfd4;
		      fd = forward->rfd4->fd;
		    }
