if (DECRYPT_KEY_ENABLED (multi, ks)
		  && key_id == ks->key_id
		  && ks->authenticated
#ifdef ENABLE_DEF_AUTH
		  && !ks->auth_deferred
#endif
		  && link_socket_actual_match (from, &ks->remote_addr))
		{
		  /* return appropriate data channel decrypt key in opt */
		  opt->key_ctx_bi = &ks->key;
		  opt->packet_id = multi->opt.replay ? &ks->packet_id : NULL;
		  opt->pid_persist = NULL;
		  opt->flags &= multi->opt.crypto_flags_and;
		  opt->flags |= multi->opt.crypto_flags_or;

		  ASSERT (buf_advance (buf, 1));
		  if (op == P_DATA_V2)
		    {
		      if (buf->len < 4)
			{
			  msg (D_TLS_ERRORS, "Protocol error: received P_DATA_V2 from %s but length is < 4",
				print_link_socket_actual (from, &gc));
			  goto error;
			}
		      ASSERT (buf_advance (buf, 3));
		    }

		  ++ks->n_packets;
		  ks->n_bytes += buf->len;
		  dmsg (D_TLS_KEYSELECT,
		       "TLS: tls_pre_decrypt, key_id=%d, IP=%s",
		       key_id, print_link_socket_actual (from, &gc));
		  gc_free (&gc);
		  return ret;
		}
