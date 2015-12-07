#ifdef HAVE_IPV6
if (source->sa.sa_family == AF_INET6)
    {
      opt->family = htons(2);
      opt->source_netmask = daemon->addr6_netmask;
      addrp = &source->in6.sin6_addr;
    }
  else
#endif
    {
      opt->family = htons(1);
      opt->source_netmask = daemon->addr4_netmask;
      addrp = &source->in.sin_addr;
    }
