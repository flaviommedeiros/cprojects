if (     ((i->ifi_addr->sa_family == AF_INET)
#if HAVE_IPV6
					  || (i->ifi_addr->sa_family == AF_INET6)
#endif
				) &&  (i->ifi_flags & IFF_UP) && !(i->ifi_flags & IFF_POINTOPOINT))
				{
				if (i->ifi_flags & IFF_LOOPBACK)
					{
					if (firstLoopback == NULL)
						firstLoopback = i;
					}
				else
					{
					if (SetupOneInterface(m, i->ifi_addr, i->ifi_netmask, i->ifi_name, i->ifi_index) == 0)
						if (i->ifi_addr->sa_family == AF_INET)
							foundav4 = mDNStrue;
					}
				}
