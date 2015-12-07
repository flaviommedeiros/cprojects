#ifdef HAVE_DHCP6
if (is6)
    {
      if (new->flags & (DHOPT_VENDOR | DHOPT_ENCAPSULATE))
	ret_err(_("unsupported encapsulation for IPv6 option"));
      
      if (opt_len == 0 &&
	  !(new->flags & DHOPT_RFC3925))
	opt_len = lookup_dhcp_len(AF_INET6, new->opt);
    }
  else
#endif
    if (opt_len == 0 &&
	!(new->flags & (DHOPT_VENDOR | DHOPT_ENCAPSULATE | DHOPT_RFC3925)))
      opt_len = lookup_dhcp_len(AF_INET, new->opt);
