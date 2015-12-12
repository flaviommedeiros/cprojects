switch (socktype)
    {
#ifdef SOCK_STREAM
    case SOCK_STREAM:
      return ___FIX(-1);
#endif

#ifdef SOCK_DGRAM
    case SOCK_DGRAM:
      return ___FIX(-2);
#endif

#ifdef SOCK_RAW
    case SOCK_RAW:
      return ___FIX(-3);
#endif
    }
