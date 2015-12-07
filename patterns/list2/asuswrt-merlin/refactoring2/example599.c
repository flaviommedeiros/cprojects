#if 0
if (ice_st->ice->role == PJ_ICE_SESS_ROLE_CONTROLLING)
#endif
    {
        for (i=0; i<ice_st->comp_cnt; ++i) {
            pj_ice_strans_comp *comp = ice_st->comp[i];
            /* Try to build outgoing tcp sock connection to reflx remote addr */
            if (comp->tcp_sock) {
				unsigned j;
				// 2013-10-17 DEAN, handle cached check list first.
				for (j=0; j<ice_st->ice->cached_clist.count; ++j) {
					pj_ice_sess_check *check = &ice_st->ice->cached_clist.checks[j];
					pj_ice_sess_cand *rcand = check->rcand;
					if (rcand->comp_id==i+1 && 
						(rcand->type == PJ_ICE_CAND_TYPE_SRFLX_TCP ||
						rcand->type == PJ_ICE_CAND_TYPE_HOST_TCP)) {

							if (0 && rcand->type == PJ_ICE_CAND_TYPE_SRFLX_TCP && 
								rcand->tcp_type == PJ_ICE_CAND_TCP_TYPE_PASSIVE) {
									// DEAN check if stun's mapped public address is same with remote endpoint's.
									// If true it represent remote endpoint and ourself use same router.
									// So we don't make external connection.
									pj_sockaddr *pub_addr = pj_stun_sock_get_mapped_addr(comp->stun_sock);
									pj_sockaddr rem_pub_addr;
									pj_sockaddr_cp(&rem_pub_addr, &rcand->addr);
									pj_sockaddr_set_port(&rem_pub_addr, pj_sockaddr_get_port(pub_addr));
									if (pj_sockaddr_cmp(pub_addr, &rem_pub_addr) == 0)
										continue;

							}

							if (rcand->type == PJ_ICE_CAND_TYPE_SRFLX_TCP)
								try_to_connect_srflx_cand = PJ_TRUE;

							status = tcp_sock_make_connection(&ice_st->cfg.stun_cfg, 
								ice_st->cfg.af, comp->tcp_sock,                                                                        
								&rcand->addr, sizeof(pj_sockaddr_in),
								&check->tcp_sess_idx, 
								j);
							if (status != PJ_SUCCESS && status != PJ_EPENDING) {
								pj_ice_strans_stop_ice(ice_st);
								return status;
							}
							tcp_sess_cnt++;
					}
				}

				// 2013-10-17 DEAN, handle active check list.
				for (j=0; j<ice_st->ice->clist.count; ++j) {
					pj_ice_sess_check *check = &ice_st->ice->clist.checks[j];
					pj_ice_sess_cand *rcand = check->rcand;
					if (rcand->comp_id==i+1 && 
						 (rcand->type == PJ_ICE_CAND_TYPE_SRFLX_TCP ||
						 rcand->type == PJ_ICE_CAND_TYPE_HOST_TCP)) {

							 if (0 && rcand->type == PJ_ICE_CAND_TYPE_SRFLX_TCP && 
								 rcand->tcp_type == PJ_ICE_CAND_TCP_TYPE_PASSIVE) {
									 // DEAN check if stun's mapped public address is same with remote endpoint's.
									 // If true it represent remote endpoint and ourself use same router.
									 // So we don't make external connection.
									 pj_sockaddr *pub_addr = pj_stun_sock_get_mapped_addr(comp->stun_sock);
									 pj_sockaddr rem_pub_addr;
									 pj_sockaddr_cp(&rem_pub_addr, &rcand->addr);
									 pj_sockaddr_set_port(&rem_pub_addr, pj_sockaddr_get_port(pub_addr));
									 if (pj_sockaddr_cmp(pub_addr, &rem_pub_addr) == 0)
										 continue;

							 }

							 if (rcand->type == PJ_ICE_CAND_TYPE_SRFLX_TCP)
								 try_to_connect_srflx_cand = PJ_TRUE;

							status = tcp_sock_make_connection(&ice_st->cfg.stun_cfg, 
								ice_st->cfg.af, comp->tcp_sock,                                                                        
								&rcand->addr, sizeof(pj_sockaddr_in),
								&check->tcp_sess_idx, 
								j);
							if (status != PJ_SUCCESS && status != PJ_EPENDING) {
								pj_ice_strans_stop_ice(ice_st);
								return status;
							}
							tcp_sess_cnt++;
					}
                }
                pj_tcp_sock_set_stun_session_user_data(comp->tcp_sock, ice_st, comp->comp_id);
            }
        }
    }
