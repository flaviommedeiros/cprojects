switch (IP_NODE(i)->type) {
			case ipv4:
				re = memcmp (&SOCKET_ADDR_IPv4(sock)->sin_addr, &IP_NODE(i)->ip, 4);
				/*
				printf ("4 remote "); print_ip(ipv4, &SOCKET_ADDRESS_IPv4(sock)); printf ("\n");
				printf ("4 list   "); print_ip(ipv4, &IP_NODE(i)->ip); printf ("\n");
				*/
				TRACE (ENTRIES, "IPv4 address (%x)%s matched (ip=%x)\n",
				       IP_NODE(i)->ip.ip4,
				       re ? " haven't" : "",
				       SOCKET_ADDR_IPv4(sock)->sin_addr);
				break;
#ifdef HAVE_IPV6
			case ipv6:
				re = (! IN6_ARE_ADDR_EQUAL (&SOCKET_ADDR_IPv6(sock)->sin6_addr, &IP_NODE(i)->ip.ip6));

				/* re = memcmp (&SOCKET_ADDR_IPv6(sock)->sin6_addr, &IP_NODE(i)->ip, 16); */

				/*
				printf ("6 family=%d, ipv6=%d\n", SOCKET_ADDR_IPv6(sock)->sin6_family, ipv6);
				printf ("6 port=%d\n",            SOCKET_ADDR_IPv6(sock)->sin6_port);
				printf ("6 remote "); print_ip(ipv6, &SOCKET_ADDRESS_IPv6(sock)); printf ("\n");
				printf ("6 list   "); print_ip(ipv6, &IP_NODE(i)->ip); printf ("\n");
				printf ("6 re = %d\n", re);
				*/
				break;
#endif
			default:
				SHOULDNT_HAPPEN;
				return ret_error;
			}
