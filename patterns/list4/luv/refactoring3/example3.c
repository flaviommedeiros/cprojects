switch (num) {
#ifdef AF_UNIX
  case AF_UNIX: return "unix";
#endif
#ifdef AF_INET
  case AF_INET: return "inet";
#endif
#ifdef AF_INET6
  case AF_INET6: return "inet6";
#endif
#ifdef AF_IPX
  case AF_IPX: return "ipx";
#endif
#ifdef AF_NETLINK
  case AF_NETLINK: return "netlink";
#endif
#ifdef AF_X25
  case AF_X25: return "x25";
#endif
#ifdef AF_AX25
  case AF_AX25: return "ax25";
#endif
#ifdef AF_ATMPVC
  case AF_ATMPVC: return "atmpvc";
#endif
#ifdef AF_APPLETALK
  case AF_APPLETALK: return "appletalk";
#endif
#ifdef AF_PACKET
  case AF_PACKET: return "packet";
#endif
  }
