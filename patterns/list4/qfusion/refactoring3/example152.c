switch(sa->sa_family) {
#ifdef ENABLE_IPV6
    case AF_INET6:
      Curl_inet_ntop(sa->sa_family, &sa6->sin6_addr, hbuf, sizeof(hbuf));
      break;
#endif
    default:
      Curl_inet_ntop(sa->sa_family, &sa4->sin_addr, hbuf, sizeof(hbuf));
      break;
    }
