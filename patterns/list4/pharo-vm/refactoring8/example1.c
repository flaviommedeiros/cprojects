static socketOption socketOptions[]= {
  { "SO_DEBUG",			SOL_SOCKET,	SO_DEBUG,          1 },
  { "SO_REUSEADDR",		SOL_SOCKET,	SO_REUSEADDR,      1 },
  { "SO_DONTROUTE",		SOL_SOCKET,	SO_DONTROUTE,      1 },
  { "SO_BROADCAST",		SOL_SOCKET,	SO_BROADCAST,      1 },
  { "SO_SNDBUF",		SOL_SOCKET,	SO_SNDBUF,         1 },
  { "SO_RCVBUF",		SOL_SOCKET,	SO_RCVBUF,         1 },
  { "SO_KEEPALIVE",		SOL_SOCKET,	SO_KEEPALIVE,      1 },
  { "SO_OOBINLINE",		SOL_SOCKET,	SO_OOBINLINE,      1 },
  { "SO_LINGER",		SOL_SOCKET,	SO_LINGER,         1 },
  { "IP_MULTICAST_IF",		SOL_IP,		IP_MULTICAST_IF,   1 },
  { "IP_MULTICAST_TTL",		SOL_IP,		IP_MULTICAST_TTL,  1 },
  { "IP_MULTICAST_LOOP",	SOL_IP,		IP_MULTICAST_LOOP, 1 },
  { "TCP_NODELAY",		SOL_TCP,	TCP_NODELAY,       1 },
  { "SO_RCVLOWAT",		SOL_SOCKET,	SO_RCVLOWAT,       1 },
  { "SO_SNDLOWAT",		SOL_SOCKET,	SO_SNDLOWAT,       1 },

  /* multicast support */
  {"IP_ADD_MEMBERSHIP",         SOL_IP,         IP_ADD_MEMBERSHIP,  100},
  {"IP_DROP_MEMBERSHIP",        SOL_IP,         IP_DROP_MEMBERSHIP, 100},

#if 0
  /* WSAIoctl() support */
  {"SIO_GET_BROADCAST_ADDRESS",	0,	SIO_GET_BROADCAST_ADDRESS, 200},
#endif
  { (char *)0,			0,		0,                  0 }
};
