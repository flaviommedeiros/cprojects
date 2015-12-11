switch (ai->ai_family) {
    case AF_INET:
      sa4 = (const void *)ai->ai_addr;
      ipaddr4 = &sa4->sin_addr;
      return Curl_inet_ntop(ai->ai_family, (const void *)ipaddr4, buf,
                            bufsize);
#ifdef ENABLE_IPV6
    case AF_INET6:
      sa6 = (const void *)ai->ai_addr;
      ipaddr6 = &sa6->sin6_addr;
      return Curl_inet_ntop(ai->ai_family, (const void *)ipaddr6, buf,
                            bufsize);
#endif
    default:
      break;
  }
