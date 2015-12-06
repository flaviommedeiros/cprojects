switch (af) {
  case AF_INET:
    return (inet_pton4(src, (unsigned char *)dst));
#ifdef ENABLE_IPV6
  case AF_INET6:
    return (inet_pton6(src, (unsigned char *)dst));
#endif
  default:
    SET_ERRNO(EAFNOSUPPORT);
    return (-1);
  }
