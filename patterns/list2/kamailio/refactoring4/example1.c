#ifdef USE_DNS_FAILOVER
if (uri2dst2(&t->uac[branch].dns_h, dst, fsocket, snd_flags,
							next_hop?next_hop:uri, fproto) == 0)
#else
		/* dst filled from the uri & request (send_socket) */
		if (uri2dst2(dst, fsocket, snd_flags,
							next_hop?next_hop:uri, fproto)==0)
#endif
		{
			ret=E_BAD_ADDRESS;
			goto error01;
		}
