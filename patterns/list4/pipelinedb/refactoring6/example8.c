if (beentry->st_clientaddr.addr.ss_family == AF_INET
#ifdef HAVE_IPV6
					|| beentry->st_clientaddr.addr.ss_family == AF_INET6
#endif
					)
				{
					char		remote_host[NI_MAXHOST];
					char		remote_port[NI_MAXSERV];
					int			ret;

					remote_host[0] = '\0';
					remote_port[0] = '\0';
					ret = pg_getnameinfo_all(&beentry->st_clientaddr.addr,
											 beentry->st_clientaddr.salen,
											 remote_host, sizeof(remote_host),
											 remote_port, sizeof(remote_port),
											 NI_NUMERICHOST | NI_NUMERICSERV);
					if (ret == 0)
					{
						clean_ipv6_addr(beentry->st_clientaddr.addr.ss_family, remote_host);
						values[11] = DirectFunctionCall1(inet_in,
											   CStringGetDatum(remote_host));
						if (beentry->st_clienthostname &&
							beentry->st_clienthostname[0])
							values[12] = CStringGetTextDatum(beentry->st_clienthostname);
						else
							nulls[12] = true;
						values[13] = Int32GetDatum(atoi(remote_port));
					}
					else
					{
						nulls[11] = true;
						nulls[12] = true;
						nulls[13] = true;
					}
				}
				else if (beentry->st_clientaddr.addr.ss_family == AF_UNIX)
				{
					/*
					 * Unix sockets always reports NULL for host and -1 for
					 * port, so it's possible to tell the difference to
					 * connections we have no permissions to view, or with
					 * errors.
					 */
					nulls[11] = true;
					nulls[12] = true;
					values[13] = DatumGetInt32(-1);
				}
				else
				{
					/* Unknown address type, should never happen */
					nulls[11] = true;
					nulls[12] = true;
					nulls[13] = true;
				}
