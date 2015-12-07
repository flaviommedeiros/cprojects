if (bind(transfer->sockfd, &addr.sa, sa_len(&addr)) == -1 ||
#if defined(IP_MTU_DISCOVER) && defined(IP_PMTUDISC_DONT)
	  setsockopt(transfer->sockfd, IPPROTO_IP, IP_MTU_DISCOVER, &mtuflag, sizeof(mtuflag)) == -1 ||
#endif
	  !fix_fd(transfer->sockfd))
	{
	  if (errno == EADDRINUSE && daemon->start_tftp_port != 0)
	    {
	      if (++port <= daemon->end_tftp_port)
		{ 
		  if (listen->family == AF_INET)
		    addr.in.sin_port = htons(port);
#ifdef HAVE_IPV6
		  else
		     addr.in6.sin6_port = htons(port);
#endif
		  continue;
		}
	      my_syslog(MS_TFTP | LOG_ERR, _("unable to get free port for TFTP"));
	    }
	  free_transfer(transfer);
	  return;
	}
