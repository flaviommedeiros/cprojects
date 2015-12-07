#ifdef HAVE_DHCP6
if (prot == AF_INET6)
    t = opttab6;
  else
#endif
    t = opttab;
