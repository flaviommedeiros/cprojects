switch (protocol)
    {
#ifdef IPPROTO_UDP
    case -1:
      return IPPROTO_UDP;
#endif

#ifdef IPPROTO_TCP
    case -2:
      return IPPROTO_TCP;
#endif
    }
