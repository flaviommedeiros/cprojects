if (protocol
#ifdef AF_UNIX
        || family != AF_UNIX
#endif
        ) {
#ifdef _WIN32
      return -WSAEAFNOSUPPORT;
#else
      return -EAFNOSUPPORT;
#endif
    }
