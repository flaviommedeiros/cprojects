if (n < 0
#ifdef USE_WIN32API
      /* Under Windows, calling "connect" with a non-blocking socket
	 results in WSAEWOULDBLOCK, not WSAEINPROGRESS.  */
      && WSAGetLastError() != WSAEWOULDBLOCK
#else
      && errno != EINPROGRESS
#endif
      )
    {
#ifdef USE_WIN32API
      errno = WSAGetLastError();
#endif
      net_close (scb);
      return -1;
    }
