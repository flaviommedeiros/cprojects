if ((si->proto == PROTO_TCP)
#ifdef USE_TLS
		    || (si->proto == PROTO_TLS)
#endif /* USE_TLS */
#ifdef USE_SCTP
			|| (si->proto == PROTO_SCTP)
#endif
			){
			if (si->flags & SI_IS_MCAST){
				LM_WARN("removing entry %s:%s [%s]:%s\n",
					get_valid_proto_name(si->proto), si->name.s, 
					si->address_str.s, si->port_no_str.s);
				l = si;
				si=si->next;
				sock_listrm(list, l);
				free_sock_info(l);
			}else{
				ail=si->addr_info_lst;
				while(ail){
					if (ail->flags & SI_IS_MCAST){
						LM_WARN("removing mh entry %s:%s"
								" [%s]:%s\n",
								get_valid_proto_name(si->proto), ail->name.s, 
								ail->address_str.s, si->port_no_str.s);
						tmp_ail=ail;
						ail=ail->next;
						addr_info_listrm(&si->addr_info_lst, tmp_ail);
						free_addr_info(tmp_ail);
					}else{
						ail=ail->next;
					}
				}
				si=si->next;
			}
		} else {
			si=si->next;
		}
