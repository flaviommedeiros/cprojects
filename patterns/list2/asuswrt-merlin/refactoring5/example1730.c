#ifdef HAVE_DNSSEC
if (flags & (F_DS | F_DNSKEY))
	new->uid = addr->addr.dnssec.class;
      else
#endif
	new->addr.addr = *addr;
