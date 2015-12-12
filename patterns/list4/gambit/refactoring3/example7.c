switch (socktype)
    {
#ifdef SOCK_STREAM
    case -1:
      return SOCK_STREAM;
#endif

#ifdef SOCK_DGRAM
    case -2:
      return SOCK_DGRAM;
#endif

#ifdef SOCK_RAW
    case -3:
      return SOCK_RAW;
#endif
    }
