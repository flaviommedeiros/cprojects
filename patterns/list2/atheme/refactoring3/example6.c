switch (type)
		{
		  case T_A:
			  if (request->type != T_A)
				  return (0);

			  /*
			   * check for invalid rd_length or too many addresses
			   */
			  if (rd_length != sizeof(struct in_addr))
				  return (0);
			  v4 = (struct sockaddr_in *)&request->addr;
			  v4->sin_family = AF_INET;
			  memcpy(&v4->sin_addr, current, sizeof(struct in_addr));
			  return (1);
			  break;
#ifdef RB_IPV6
		  case T_AAAA:
			  if (request->type != T_AAAA)
				  return (0);
			  if (rd_length != sizeof(struct in6_addr))
				  return (0);
			  v6 = (struct sockaddr_in6 *)&request->addr;
			  v6->sin6_family = AF_INET6;
			  memcpy(&v6->sin6_addr, current, sizeof(struct in6_addr));
			  return (1);
			  break;
#endif
		  case T_PTR:
			  if (request->type != T_PTR)
				  return (0);
			  n = irc_dn_expand((unsigned char *)buf, (unsigned char *)eob, current,
					    hostbuf, sizeof(hostbuf));
			  if (n < 0)
				  return (0);	/* broken message */
			  else if (n == 0)
				  return (0);	/* no more answers left */

			  mowgli_strlcpy(request->name, hostbuf, IRCD_RES_HOSTLEN + 1);

			  return (1);
			  break;
		  case T_CNAME:
			  /* real answer will follow */
			  current += rd_length;
			  break;

		  default:
			  /* XXX I'd rather just throw away the entire bogus thing
			   * but its possible its just a broken nameserver with still
			   * valid answers. But lets do some rudimentary logging for now...
			   */
			  slog(LG_DEBUG, "proc_answer(): bogus type %d", type);
			  break;
		}
