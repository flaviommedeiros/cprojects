switch(sa->sa_family) {
    case AF_INET:
      port = ntohs(sa4->sin_port);
      break;
#ifdef ENABLE_IPV6
    case AF_INET6:
      port = ntohs(sa6->sin6_port);
      break;
#endif
    default:
      continue; /* might as well skip this */
    }
