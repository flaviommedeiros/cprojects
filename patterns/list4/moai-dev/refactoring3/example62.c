switch (localaddr->sa_family) {
    case AF_INET:
      *listenport = ntohs(localaddr4.sin_port);
      break;
#ifdef ENABLE_IPV6
    case AF_INET6:
      *listenport = ntohs(localaddr6.sin6_port);
      break;
#endif
    default:
      break;
    }
