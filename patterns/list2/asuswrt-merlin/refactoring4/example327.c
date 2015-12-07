#ifndef IPV6_RECVPKTINFO
if (setsockopt (sd, IPPROTO_IPV6, IPV6_PKTINFO,
		      (void*)&pad, sizeof(pad)) < 0)
#else
      if (setsockopt (sd, IPPROTO_IPV6, IPV6_RECVPKTINFO,
		      (void*)&pad, sizeof(pad)) < 0)
#endif
	msg(M_ERR, "UDP: failed setsockopt for IPV6_RECVPKTINFO");
