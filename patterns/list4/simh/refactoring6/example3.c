if ((tcp_fconnect(so) == -1) &&
#if defined(_WIN32)
              socket_error() != WSAEINPROGRESS && socket_error() != WSAEWOULDBLOCK
#else
              (errno != EINPROGRESS) && (errno != EWOULDBLOCK)
#endif
          ) {
	    u_char code=ICMP_UNREACH_NET;
	    DEBUG_MISC(" tcp fconnect errno = %d-%s\n",
			errno,strerror(errno));
	    if(errno == ECONNREFUSED) {
	      /* ACK the SYN, send RST to refuse the connection */
	      tcp_respond(tp, ti, m, ti->ti_seq+1, (tcp_seq)0,
			  TH_RST|TH_ACK);
	    } else {
	      if(errno == EHOSTUNREACH) code=ICMP_UNREACH_HOST;
	      HTONL(ti->ti_seq);             /* restore tcp header */
	      HTONL(ti->ti_ack);
	      HTONS(ti->ti_win);
	      HTONS(ti->ti_urp);
	      m->m_data -= sizeof(struct tcpiphdr)+off-sizeof(struct tcphdr);
	      m->m_len  += sizeof(struct tcpiphdr)+off-sizeof(struct tcphdr);
	      *ip=save_ip;
	      icmp_error(m, ICMP_UNREACH,code, 0,strerror(errno));
	    }
            tcp_close(tp);
	    m_free(m);
	  } else {
	    /*
	     * Haven't connected yet, save the current mbuf
	     * and ti, and return
	     * XXX Some OS's don't tell us whether the connect()
	     * succeeded or not.  So we must time it out.
	     */
	    so->so_m = m;
	    so->so_ti = ti;
	    tp->t_timer[TCPT_KEEP] = TCPTV_KEEP_INIT;
	    tp->t_state = TCPS_SYN_RECEIVED;
	    tcp_template(tp);
	  }
