switch (family)
	{
		case AF_INET:
			{
				struct sockaddr_in mask4;
				long		maskl;

				if (bits < 0 || bits > 32)
					return -1;
				memset(&mask4, 0, sizeof(mask4));
				/* avoid "x << 32", which is not portable */
				if (bits > 0)
					maskl = (0xffffffffUL << (32 - (int) bits))
						& 0xffffffffUL;
				else
					maskl = 0;
				mask4.sin_addr.s_addr = htonl(maskl);
				memcpy(mask, &mask4, sizeof(mask4));
				break;
			}

#ifdef HAVE_IPV6
		case AF_INET6:
			{
				struct sockaddr_in6 mask6;
				int			i;

				if (bits < 0 || bits > 128)
					return -1;
				memset(&mask6, 0, sizeof(mask6));
				for (i = 0; i < 16; i++)
				{
					if (bits <= 0)
						mask6.sin6_addr.s6_addr[i] = 0;
					else if (bits >= 8)
						mask6.sin6_addr.s6_addr[i] = 0xff;
					else
					{
						mask6.sin6_addr.s6_addr[i] =
							(0xff << (8 - (int) bits)) & 0xff;
					}
					bits -= 8;
				}
				memcpy(mask, &mask6, sizeof(mask6));
				break;
			}
#endif
		default:
			return -1;
	}
