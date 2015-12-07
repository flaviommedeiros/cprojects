#ifdef ENABLE_DEBUG
if (!c->options.gremlin || ask_gremlin (c->options.gremlin))
#endif
	{
	  /*
	   * Let the traffic shaper know how many bytes
	   * we wrote.
	   */
#ifdef ENABLE_FEATURE_SHAPER
	  if (c->options.shaper)
	    shaper_wrote_bytes (&c->c2.shaper, BLEN (&c->c2.to_link)
				+ datagram_overhead (c->options.ce.proto));
#endif
	  /*
	   * Let the pinger know that we sent a packet.
	   */
	  if (c->options.ping_send_timeout)
	    event_timeout_reset (&c->c2.ping_send_interval);

#if PASSTOS_CAPABILITY
	  /* Set TOS */
	  link_socket_set_tos (c->c2.link_socket);
#endif

	  /* Log packet send */
#ifdef LOG_RW
	  if (c->c2.log_rw)
	    fprintf (stderr, "W");
#endif
	  msg (D_LINK_RW, "%s WRITE [%d] to %s: %s",
	       proto2ascii (c->c2.link_socket->info.proto, true),
	       BLEN (&c->c2.to_link),
	       print_link_socket_actual (c->c2.to_link_addr, &gc),
	       PROTO_DUMP (&c->c2.to_link, &gc));

	  /* Packet send complexified by possible Socks5 usage */
	  {
	    struct link_socket_actual *to_addr = c->c2.to_link_addr;
#ifdef ENABLE_SOCKS
	    int size_delta = 0;
#endif

#ifdef ENABLE_SOCKS
	    /* If Socks5 over UDP, prepend header */
	    socks_preprocess_outgoing_link (c, &to_addr, &size_delta);
#endif
	    /* Send packet */
	    size = link_socket_write (c->c2.link_socket,
				      &c->c2.to_link,
				      to_addr);

#ifdef ENABLE_SOCKS
	    /* Undo effect of prepend */
	    link_socket_write_post_size_adjust (&size, size_delta, &c->c2.to_link);
#endif
	  }

	  if (size > 0)
	    {
	      c->c2.max_send_size_local = max_int (size, c->c2.max_send_size_local);
	      c->c2.link_write_bytes += size;
	      link_write_bytes_global += size;
#ifdef ENABLE_MEMSTATS
	      if (mmap_stats)
		mmap_stats->link_write_bytes = link_write_bytes_global;
#endif
#ifdef ENABLE_MANAGEMENT
	      if (management)
		{
		  management_bytes_out (management, size);
#ifdef MANAGEMENT_DEF_AUTH
		  management_bytes_server (management, &c->c2.link_read_bytes, &c->c2.link_write_bytes, &c->c2.mda_context);
#endif
		}
#endif
	    }
	}
