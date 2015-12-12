switch (IP_NODE(i)->type) {
			case ipv4:
				masqued_list.ip4.s_addr   = (IP_NODE(i)->ip.ip4.s_addr &
				                             SUBNET_NODE(i)->mask.ip4.s_addr);
				masqued_remote.ip4.s_addr = (SOCKET_ADDR_IPv4(sock)->sin_addr.s_addr &
				                             SUBNET_NODE(i)->mask.ip4.s_addr);

				TRACE (ENTRIES, "Checking IPv4 net: (mask=%x) %x == %x ?\n",
				       SUBNET_NODE(i)->mask.ip4.s_addr,
				       masqued_remote.ip4.s_addr,
				       masqued_list.ip4.s_addr);

				if (masqued_remote.ip4.s_addr == masqued_list.ip4.s_addr) {
					return ret_ok;
				}

				break;
#ifdef HAVE_IPV6
			case ipv6:
			{
				cherokee_boolean_t equal = true;

				for (j=0; j<16; j++) {
					masqued_list.ip6.s6_addr[j] = (
					        IP_NODE(i)->ip.ip6.s6_addr[j] &
					        SUBNET_NODE(i)->mask.ip6.s6_addr[j]);
					masqued_remote.ip6.s6_addr[j] = (
					        SOCKET_ADDR_IPv6(sock)->sin6_addr.s6_addr[j] &
					        SUBNET_NODE(i)->mask.ip6.s6_addr[j]);

					if (masqued_list.ip6.s6_addr[j] !=
					    masqued_remote.ip6.s6_addr[j])
					{
						equal = false;
						break;
					}
				}

				TRACE (ENTRIES, "Checking IPv6 net: (mask=%x) %x == %x ?\n",
				       SUBNET_NODE(i)->mask.ip6.s6_addr,
				       masqued_remote.ip6.s6_addr,
				       masqued_list.ip6.s6_addr);


				if (equal == true) {
					return ret_ok;
				}
				break;
			}
#endif
			default:
				SHOULDNT_HAPPEN;
				return ret_error;
			}
