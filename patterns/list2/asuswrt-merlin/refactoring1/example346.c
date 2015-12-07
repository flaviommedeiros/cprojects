if (ah->flags & AH_HOSTS)
		     total_size = read_hostsfile(path, ah->index, total_size, rhash, revhashsz);
#ifdef HAVE_DHCP
		   else if (ah->flags & (AH_DHCP_HST | AH_DHCP_OPT))
		     option_read_dynfile(path, ah->flags);
#endif
