#ifdef HAVE_IPV6
if (((addrlist->flags & ADDRLIST_IPV6) ? T_AAAA : T_A) == type)
#endif
			    {
#ifdef HAVE_IPV6
			      if (addrlist->flags & ADDRLIST_REVONLY)
				continue;
#endif	
			      ans = 1;	
			      if (!dryrun)
				{
				  gotit = 1;
				  log_query(F_FORWARD | F_CONFIG | flag, name, &addrlist->addr, NULL);
				  if (add_resource_record(header, limit, &trunc, nameoffset, &ansp, 
							  daemon->local_ttl, NULL, type, C_IN, 
							  type == T_A ? "4" : "6", &addrlist->addr))
				    anscount++;
				}
			    }
