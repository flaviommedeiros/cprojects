switch (protocol)
    {
#ifdef IPPROTO_UDP
    case IPPROTO_UDP:
      return ___FIX(-1);
#endif

#ifdef IPPROTO_TCP
    case IPPROTO_TCP:
      return ___FIX(-2);
#endif
    }
