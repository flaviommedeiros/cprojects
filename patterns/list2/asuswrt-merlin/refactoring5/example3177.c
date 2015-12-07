#ifdef HAVE_AUTH
if (auth_dns)
	m = answer_auth(header, ((char *) header) + 65536, (size_t)size, now, &peer_addr, local_auth);
      else
#endif
	{
	  /* m > 0 if answered from cache */
	  m = answer_request(header, ((char *) header) + 65536, (size_t)size, 
			     dst_addr_4, netmask, now, &ad_question, &do_bit);
	  
	  /* Do this by steam now we're not in the select() loop */
	  check_log_writer(1); 
	  
	  if (m == 0)
	    {
	      unsigned int flags = 0;
	      struct all_addr *addrp = NULL;
	      int type = 0;
	      char *domain = NULL;
	      
	      if (option_bool(OPT_ADD_MAC))
		size = add_mac(header, size, ((char *) header) + 65536, &peer_addr);
	      	
	      if (option_bool(OPT_CLIENT_SUBNET))
		{
		  size_t new = add_source_addr(header, size, ((char *) header) + 65536, &peer_addr);
		  if (size != new)
		    {
		      size = new;
		      check_subnet = 1;
		    }
		}

	      if (gotname)
		flags = search_servers(now, &addrp, gotname, daemon->namebuff, &type, &domain, &norebind);
	      
	      if (type != 0  || option_bool(OPT_ORDER) || !daemon->last_server)
		last_server = daemon->servers;
	      else
		last_server = daemon->last_server;
	      
	      if (!flags && last_server)
		{
		  struct server *firstsendto = NULL;
#ifdef HAVE_DNSSEC
		  unsigned char *newhash, hash[HASH_SIZE];
		  if ((newhash = hash_questions(header, (unsigned int)size, daemon->namebuff)))
		    memcpy(hash, newhash, HASH_SIZE);
		  else
		    memset(hash, 0, HASH_SIZE);
#else
		  unsigned int crc = questions_crc(header, (unsigned int)size, daemon->namebuff);
#endif		  
		  /* Loop round available servers until we succeed in connecting to one.
		     Note that this code subtley ensures that consecutive queries on this connection
		     which can go to the same server, do so. */
		  while (1) 
		    {
		      if (!firstsendto)
			firstsendto = last_server;
		      else
			{
			  if (!(last_server = last_server->next))
			    last_server = daemon->servers;
			  
			  if (last_server == firstsendto)
			    break;
			}
		      
		      /* server for wrong domain */
		      if (type != (last_server->flags & SERV_TYPE) ||
			  (type == SERV_HAS_DOMAIN && !hostname_isequal(domain, last_server->domain)) ||
			  (last_server->flags & (SERV_LITERAL_ADDRESS | SERV_LOOP)))
			continue;
		      
		      if (last_server->tcpfd == -1)
			{
			  if ((last_server->tcpfd = socket(last_server->addr.sa.sa_family, SOCK_STREAM, 0)) == -1)
			    continue;
			  
#ifdef HAVE_CONNTRACK
			  /* Copy connection mark of incoming query to outgoing connection. */
			  if (option_bool(OPT_CONNTRACK))
			    {
			      unsigned int mark;
			      struct all_addr local;
#ifdef HAVE_IPV6		      
			      if (local_addr->sa.sa_family == AF_INET6)
				local.addr.addr6 = local_addr->in6.sin6_addr;
			      else
#endif
				local.addr.addr4 = local_addr->in.sin_addr;
			      
			      if (get_incoming_mark(&peer_addr, &local, 1, &mark))
				setsockopt(last_server->tcpfd, SOL_SOCKET, SO_MARK, &mark, sizeof(unsigned int));
			    }
#endif	
		      
			  if ((!local_bind(last_server->tcpfd,  &last_server->source_addr, last_server->interface, 1) ||
			       connect(last_server->tcpfd, &last_server->addr.sa, sa_len(&last_server->addr)) == -1))
			    {
			      close(last_server->tcpfd);
			      last_server->tcpfd = -1;
			      continue;
			    }
			  
#ifdef HAVE_DNSSEC
			  if (option_bool(OPT_DNSSEC_VALID))
			    {
			      size_t new_size = add_do_bit(header, size, ((char *) header) + 65536);
			      
			      /* For debugging, set Checking Disabled, otherwise, have the upstream check too,
				 this allows it to select auth servers when one is returning bad data. */
			      if (option_bool(OPT_DNSSEC_DEBUG))
				header->hb4 |= HB4_CD;
			      
			      if (size != new_size)
				added_pheader = 1;
			      
			      size = new_size;
			    }
#endif
			}
		      
		      *length = htons(size);

		      /* get query name again for logging - may have been overwritten */
		      if (!(gotname = extract_request(header, (unsigned int)size, daemon->namebuff, &qtype)))
			strcpy(daemon->namebuff, "query");
		      
		      if (!read_write(last_server->tcpfd, packet, size + sizeof(u16), 0) ||
			  !read_write(last_server->tcpfd, &c1, 1, 1) ||
			  !read_write(last_server->tcpfd, &c2, 1, 1) ||
			  !read_write(last_server->tcpfd, payload, (c1 << 8) | c2, 1))
			{
			  close(last_server->tcpfd);
			  last_server->tcpfd = -1;
			  continue;
			} 
		      
		      m = (c1 << 8) | c2;
		      
		      if (last_server->addr.sa.sa_family == AF_INET)
			log_query(F_SERVER | F_IPV4 | F_FORWARD, daemon->namebuff, 
				  (struct all_addr *)&last_server->addr.in.sin_addr, NULL); 
#ifdef HAVE_IPV6
		      else
			log_query(F_SERVER | F_IPV6 | F_FORWARD, daemon->namebuff, 
				  (struct all_addr *)&last_server->addr.in6.sin6_addr, NULL);
#endif 

#ifdef HAVE_DNSSEC
		      if (option_bool(OPT_DNSSEC_VALID) && !checking_disabled)
			{
			  int keycount = DNSSEC_WORK; /* Limit to number of DNSSEC questions, to catch loops and avoid filling cache. */
			  int status = tcp_key_recurse(now, STAT_TRUNCATED, header, m, 0, daemon->namebuff, daemon->keyname, last_server, &keycount);
			  char *result, *domain = "result";

			  if (status == STAT_INSECURE_DS)
			    {
			      /* We only cache sigs when we've validated a reply.
				 Avoid caching a reply with sigs if there's a vaildated break in the 
				 DS chain, so we don't return replies from cache missing sigs. */
			      status = STAT_INSECURE;
			      no_cache_dnssec = 1;
			    }
			  
			  if (keycount == 0)
			    {
			      result = "ABANDONED";
			      status = STAT_BOGUS;
			    }
			  else
			    result = (status == STAT_SECURE ? "SECURE" : (status == STAT_INSECURE ? "INSECURE" : "BOGUS"));
			  
			  if (status == STAT_BOGUS && extract_request(header, m, daemon->namebuff, NULL))
			    domain = daemon->namebuff;

			  log_query(F_KEYTAG | F_SECSTAT, domain, NULL, result);
			  
			  if (status == STAT_BOGUS)
			    {
			      no_cache_dnssec = 1;
			      bogusanswer = 1;
			    }

			  if (status == STAT_SECURE)
			    cache_secure = 1;
			}
#endif

		      /* restore CD bit to the value in the query */
		      if (checking_disabled)
			header->hb4 |= HB4_CD;
		      else
			header->hb4 &= ~HB4_CD;
		      
		      /* There's no point in updating the cache, since this process will exit and
			 lose the information after a few queries. We make this call for the alias and 
			 bogus-nxdomain side-effects. */
		      /* If the crc of the question section doesn't match the crc we sent, then
			 someone might be attempting to insert bogus values into the cache by 
			 sending replies containing questions and bogus answers. */
#ifdef HAVE_DNSSEC
		      newhash = hash_questions(header, (unsigned int)m, daemon->namebuff);
		      if (!newhash || memcmp(hash, newhash, HASH_SIZE) != 0)
			{ 
			  m = 0;
			  break;
			}
#else			  
		      if (crc != questions_crc(header, (unsigned int)m, daemon->namebuff))
			{
			  m = 0;
			  break;
			}
#endif

		      m = process_reply(header, now, last_server, (unsigned int)m, 
					option_bool(OPT_NO_REBIND) && !norebind, no_cache_dnssec, cache_secure, bogusanswer,
					ad_question, do_bit, added_pheader, check_subnet, &peer_addr); 
		      
		      break;
		    }
		}
	
	      /* In case of local answer or no connections made. */
	      if (m == 0)
		m = setup_reply(header, (unsigned int)size, addrp, flags, daemon->local_ttl);
	    }
	}
