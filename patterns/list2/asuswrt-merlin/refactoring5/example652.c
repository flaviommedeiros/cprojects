#ifdef HAVE_AUTH
if (auth_dns)
    {
      m = answer_auth(header, ((char *) header) + daemon->packet_buff_sz, (size_t)n, now, &source_addr, local_auth);
      if (m >= 1)
	{
	  send_from(listen->fd, option_bool(OPT_NOWILD) || option_bool(OPT_CLEVERBIND),
		    (char *)header, m, &source_addr, &dst_addr, if_index);
	  daemon->auth_answer++;
	}
    }
  else
#endif
    {
      int ad_reqd, do_bit;
      m = answer_request(header, ((char *) header) + daemon->packet_buff_sz, (size_t)n, 
			 dst_addr_4, netmask, now, &ad_reqd, &do_bit);
      
      if (m >= 1)
	{
	  send_from(listen->fd, option_bool(OPT_NOWILD) || option_bool(OPT_CLEVERBIND),
		    (char *)header, m, &source_addr, &dst_addr, if_index);
	  daemon->local_answer++;
	}
      else if (forward_query(listen->fd, &source_addr, &dst_addr, if_index,
			     header, (size_t)n, now, NULL, ad_reqd, do_bit))
	daemon->queries_forwarded++;
      else
	daemon->local_answer++;
    }
