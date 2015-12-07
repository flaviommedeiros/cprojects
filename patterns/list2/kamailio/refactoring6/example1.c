if ((port==snd_i->send_sock->port_no) && 
					(proto==snd_i->send_sock->proto) &&
#ifdef USE_COMP
					(msg->rcv.comp==snd_i->comp) &&
#endif
					(ip_addr_cmp(ip, &snd_i->send_sock->address)))
				return 0;
			else {
				LUMP_SET_COND_TRUE(l);
				return 1;
			}
