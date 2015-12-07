#ifdef ENABLE_IPV6
if(ipv6)
	{
		for(lan_addr = lan_addrs.lh_first; lan_addr != NULL; lan_addr = lan_addr->list.le_next)
		{
			if(AddMulticastMembershipIPv6(s, lan_addr->index) < 0)
			{
				syslog(LOG_WARNING,
				       "Failed to add IPv6 multicast membership for interface %s",
				       lan_addr->str ? lan_addr->str : "NULL");
			}
		}
	}
	else
#endif
	{
		for(lan_addr = lan_addrs.lh_first; lan_addr != NULL; lan_addr = lan_addr->list.le_next)
		{
			if(AddMulticastMembership(s, lan_addr) < 0)
			{
				syslog(LOG_WARNING,
				       "Failed to add multicast membership for interface %s",
				       strlen(lan_addr->str) ? lan_addr->str : "NULL");
			}
		}
	}
