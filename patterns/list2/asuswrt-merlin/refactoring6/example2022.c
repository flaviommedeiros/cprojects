if (
#ifdef WIN32
    status == WSAEWOULDBLOCK
#else
    status == EINPROGRESS
#endif
  )
    {
      while (true)
	{
	  fd_set writes;
	  struct timeval tv;

	  FD_ZERO (&writes);
	  FD_SET (sd, &writes);
	  tv.tv_sec = 0;
	  tv.tv_usec = 0;

	  status = select (sd + 1, NULL, &writes, NULL, &tv);

	  if (signal_received)
	    {
	      get_signal (signal_received);
	      if (*signal_received)
		{
		  status = 0;
		  break;
		}
	    }
	  if (status < 0)
	    {
	      status = openvpn_errno ();
	      break;
	    }
	  if (status <= 0)
	    {
	      if (--connect_timeout < 0)
		{
		  status = ETIMEDOUT;
		  break;
		}
	      openvpn_sleep (1);
	      continue;
	    }

	  /* got it */
	  {
	    int val = 0;
	    socklen_t len;

	    len = sizeof (val);
	    if (getsockopt (sd, SOL_SOCKET, SO_ERROR, (void *) &val, &len) == 0
		&& len == sizeof (val))
	      status = val;
	    else
	      status = openvpn_errno ();
	    break;
	  }
	}
    }
