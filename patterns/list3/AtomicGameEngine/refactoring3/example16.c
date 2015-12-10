switch (af) {
  case AF_INET:
    return inet_ntop4((const unsigned char*)src, buf, size);
#ifdef ENABLE_IPV6
  case AF_INET6:
    return inet_ntop6((const unsigned char*)src, buf, size);
#endif
  default:
    SET_ERRNO(EAFNOSUPPORT);
    return NULL;
  }
