static const int protos[] = {
    SOCK_STREAM,
    SOCK_STREAM,
    SOCK_STREAM,
    SOCK_DGRAM,
    SOCK_STREAM,
    SOCK_STREAM
#if defined(NS_ENABLE_IPV6)
    ,
    SOCK_DGRAM,
    SOCK_STREAM
#endif
  };
