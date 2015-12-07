#ifdef ENABLE_PF
if (!pf_addr_test (c, e2, "tun_tap_src_addr"))
		    {
		      msg (D_PF_DROPPED, "PF: addr[%s] -> client packet dropped by packet filter",
			   mroute_addr_print_ex (&src, MAPF_SHOW_ARP, &gc));
		      buf_reset_len (&c->c2.buf);
		    }
		  else
#endif
		  {
		    if (multi_output_queue_ready (m, m->pending))
		      {
			/* transfer packet pointer from top-level context buffer to instance */
			c->c2.buf = m->top.c2.buf;
		      }
		    else
		      {
			/* drop packet */
			msg (D_MULTI_DROPPED, "MULTI: packet dropped due to output saturation (multi_process_incoming_tun)");
			buf_reset_len (&c->c2.buf);
		      }
		  }
