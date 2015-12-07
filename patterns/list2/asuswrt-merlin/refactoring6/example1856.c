if (     ((i->ifi_addr->sa_family == AF_INET)
#ifdef mDNSIPv6Support
					  || (i->ifi_addr->sa_family == AF_INET6)
#endif
				) &&  (i->ifi_flags & IFF_UP) && !(i->ifi_flags & IFF_POINTOPOINT) )
				{
				if (i->ifi_flags & IFF_LOOPBACK)
					{
					if (firstLoopback == NULL)
						firstLoopback = i;
					}
				else
					{
					if (SetupOneInterface(m, i->ifi_addr, i->ifi_name) == 0)
						if (i->ifi_addr->sa_family == AF_INET)
							foundav4 = mDNStrue;
					}
				}
