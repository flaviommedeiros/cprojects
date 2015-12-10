switch(af) {
  case AF_INET:
    addrsize = sizeof(struct in_addr);
    addrentry = (void *)&buf->addrentry.ina4;
    memcpy(addrentry, inaddr, sizeof(struct in_addr));
    break;
#ifdef ENABLE_IPV6
  case AF_INET6:
    addrsize = sizeof(struct in6_addr);
    addrentry = (void *)&buf->addrentry.ina6;
    memcpy(addrentry, inaddr, sizeof(struct in6_addr));
    break;
#endif
  default:
    free(hoststr);
    free(buf);
    return NULL;
  }
