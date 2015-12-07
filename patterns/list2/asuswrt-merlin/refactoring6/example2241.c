if (ans && 
      (ans->flags & F_FORWARD) &&
#ifdef HAVE_DNSSEC
      (((ans->flags & (F_DNSKEY | F_DS)) == (prot & (F_DNSKEY | F_DS))) || (prot & F_NSIGMATCH)) &&
#endif
      (ans->flags & prot) &&     
      hostname_isequal(cache_get_name(ans), name))
    return ans;
