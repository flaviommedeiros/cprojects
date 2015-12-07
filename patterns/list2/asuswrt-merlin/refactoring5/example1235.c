#ifdef ENABLE_MANAGEMENT
if (e->arg == MTCP_MANAGEMENT)
	    {
	      ASSERT (management);
	      management_io (management);
	    }
	  else
#endif
	  /* incoming data on TUN? */
	  if (e->arg == MTCP_TUN)
	    {
	      if (e->rwflags & EVENT_WRITE)
		multi_tcp_action (m, NULL, TA_TUN_WRITE, false);
	      else if (e->rwflags & EVENT_READ)
		multi_tcp_action (m, NULL, TA_TUN_READ, false);
	    }
	  /* new incoming TCP client attempting to connect? */
	  else if (e->arg == MTCP_SOCKET)
	    {
	      struct multi_instance *mi;
	      ASSERT (m->top.c2.link_socket);
	      socket_reset_listen_persistent (m->top.c2.link_socket);
	      mi = multi_create_instance_tcp (m);
	      if (mi)
		multi_tcp_action (m, mi, TA_INITIAL, false);
	    }
	  /* signal received? */
	  else if (e->arg == MTCP_SIG)
	    {
	      get_signal (&m->top.sig->signal_received);
	    }
