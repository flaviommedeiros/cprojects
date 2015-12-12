switch (family)
    {
      case AF_INET:
        switch (type)
        {
          case SOCK_STREAM: result = "tcp"; break;
          case  SOCK_DGRAM: result = "udp"; break;
        }
        break;
      case AF_INET6:
        switch (type)
        {
          case SOCK_STREAM: result = "tcp6"; break;
          case  SOCK_DGRAM: result = "udp6"; break;
        }
        break;
#ifndef G_OS_WIN32
      case AF_UNIX:
        switch (type)
        {
          case SOCK_STREAM: result = "unix:stream"; break;
          case  SOCK_DGRAM: result = "unix:dgram";  break;
        }
        break;
#endif
    }
