#ifdef HAVE_IPV6
if (addr->sa.sa_family == AF_INET6)
    return sizeof(addr->in6);
  else
#endif
    return sizeof(addr->in);
