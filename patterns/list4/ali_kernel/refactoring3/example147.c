switch (sm->smt_class) {
	case SMT_NIF :
		if (smt_check_para(smc,sm,plist_nif)) {
			DB_SMT("SMT: NIF with para problem, ignoring\n",0,0) ;
			break ;
		} ;
		switch (sm->smt_type) {
		case SMT_ANNOUNCE :
		case SMT_REQUEST :
			if (!(fs & C_INDICATOR) && m_fc(mb) == FC_SMT_NSA
				&& is_broadcast(&sm->smt_dest)) {
				struct smt_p_state	*st ;

				/* set my UNA */
				if (!is_equal(
					&smc->mib.m[MAC0].fddiMACUpstreamNbr,
					&sm->smt_source)) {
					DB_SMT("SMT : updated my UNA = %s\n",
					addr_to_string(&sm->smt_source),0) ;
					if (!is_equal(&smc->mib.m[MAC0].
					    fddiMACUpstreamNbr,&SMT_Unknown)){
					 /* Do not update unknown address */
					 smc->mib.m[MAC0].fddiMACOldUpstreamNbr=
					 smc->mib.m[MAC0].fddiMACUpstreamNbr ;
					}

					smc->mib.m[MAC0].fddiMACUpstreamNbr =
						sm->smt_source ;
					smt_srf_event(smc,
						SMT_EVENT_MAC_NEIGHBOR_CHANGE,
						INDEX_MAC,0) ;
					smt_echo_test(smc,0) ;
				}
				smc->sm.smt_tvu = smt_get_time() ;
				st = (struct smt_p_state *)
					sm_to_para(smc,sm,SMT_P_STATE) ;
				if (st) {
					smc->mib.m[MAC0].fddiMACUNDA_Flag =
					(st->st_dupl_addr & SMT_ST_MY_DUPA) ?
					TRUE : FALSE ;
					update_dac(smc,1) ;
				}
			}
			if ((sm->smt_type == SMT_REQUEST) &&
			    is_individual(&sm->smt_source) &&
			    ((!(fs & A_INDICATOR) && m_fc(mb) == FC_SMT_NSA) ||
			     (m_fc(mb) != FC_SMT_NSA))) {
				DB_SMT("SMT : replying to NIF request %s\n",
					addr_to_string(&sm->smt_source),0) ;
				smt_send_nif(smc,&sm->smt_source,
					FC_SMT_INFO,
					sm->smt_tid,
					SMT_REPLY,local) ;
			}
			break ;
		case SMT_REPLY :
			DB_SMT("SMT : received NIF response from %s\n",
				addr_to_string(&sm->smt_source),0) ;
			if (fs & A_INDICATOR) {
				smc->sm.pend[SMT_TID_NIF] = 0 ;
				DB_SMT("SMT : duplicate address\n",0,0) ;
				smc->mib.m[MAC0].fddiMACDupAddressTest =
					DA_FAILED ;
				smc->r.dup_addr_test = DA_FAILED ;
				queue_event(smc,EVENT_RMT,RM_DUP_ADDR) ;
				smc->mib.m[MAC0].fddiMACDA_Flag = TRUE ;
				update_dac(smc,1) ;
				break ;
			}
			if (sm->smt_tid == smc->sm.pend[SMT_TID_NIF]) {
				smc->sm.pend[SMT_TID_NIF] = 0 ;
				/* set my DNA */
				if (!is_equal(
					&smc->mib.m[MAC0].fddiMACDownstreamNbr,
					&sm->smt_source)) {
					DB_SMT("SMT : updated my DNA\n",0,0) ;
					if (!is_equal(&smc->mib.m[MAC0].
					 fddiMACDownstreamNbr, &SMT_Unknown)){
					 /* Do not update unknown address */
				smc->mib.m[MAC0].fddiMACOldDownstreamNbr =
					 smc->mib.m[MAC0].fddiMACDownstreamNbr ;
					}

					smc->mib.m[MAC0].fddiMACDownstreamNbr =
						sm->smt_source ;
					smt_srf_event(smc,
						SMT_EVENT_MAC_NEIGHBOR_CHANGE,
						INDEX_MAC,0) ;
					smt_echo_test(smc,1) ;
				}
				smc->mib.m[MAC0].fddiMACDA_Flag = FALSE ;
				update_dac(smc,1) ;
				smc->sm.smt_tvd = smt_get_time() ;
				smc->mib.m[MAC0].fddiMACDupAddressTest =
					DA_PASSED ;
				if (smc->r.dup_addr_test != DA_PASSED) {
					smc->r.dup_addr_test = DA_PASSED ;
					queue_event(smc,EVENT_RMT,RM_DUP_ADDR) ;
				}
			}
			else if (sm->smt_tid ==
				smc->sm.pend[SMT_TID_NIF_TEST]) {
				DB_SMT("SMT : NIF test TID ok\n",0,0) ;
			}
			else {
				DB_SMT("SMT : expected TID %lx, got %lx\n",
				smc->sm.pend[SMT_TID_NIF],sm->smt_tid) ;
			}
			break ;
		default :
			illegal = 2 ;
			break ;
		}
		break ;
	case SMT_SIF_CONFIG :	/* station information */
		if (sm->smt_type != SMT_REQUEST)
			break ;
		DB_SMT("SMT : replying to SIF Config request from %s\n",
			addr_to_string(&sm->smt_source),0) ;
		smt_send_sif_config(smc,&sm->smt_source,sm->smt_tid,local) ;
		break ;
	case SMT_SIF_OPER :	/* station information */
		if (sm->smt_type != SMT_REQUEST)
			break ;
		DB_SMT("SMT : replying to SIF Operation request from %s\n",
			addr_to_string(&sm->smt_source),0) ;
		smt_send_sif_operation(smc,&sm->smt_source,sm->smt_tid,local) ;
		break ;
	case SMT_ECF :		/* echo frame */
		switch (sm->smt_type) {
		case SMT_REPLY :
			smc->mib.priv.fddiPRIVECF_Reply_Rx++ ;
			DB_SMT("SMT: received ECF reply from %s\n",
				addr_to_string(&sm->smt_source),0) ;
			if (sm_to_para(smc,sm,SMT_P_ECHODATA) == NULL) {
				DB_SMT("SMT: ECHODATA missing\n",0,0) ;
				break ;
			}
			if (sm->smt_tid == smc->sm.pend[SMT_TID_ECF]) {
				DB_SMT("SMT : ECF test TID ok\n",0,0) ;
			}
			else if (sm->smt_tid == smc->sm.pend[SMT_TID_ECF_UNA]) {
				DB_SMT("SMT : ECF test UNA ok\n",0,0) ;
			}
			else if (sm->smt_tid == smc->sm.pend[SMT_TID_ECF_DNA]) {
				DB_SMT("SMT : ECF test DNA ok\n",0,0) ;
			}
			else {
				DB_SMT("SMT : expected TID %lx, got %lx\n",
					smc->sm.pend[SMT_TID_ECF],
					sm->smt_tid) ;
			}
			break ;
		case SMT_REQUEST :
			smc->mib.priv.fddiPRIVECF_Req_Rx++ ;
			{
			if (sm->smt_len && !sm_to_para(smc,sm,SMT_P_ECHODATA)) {
			DB_SMT("SMT: ECF with para problem,sending RDF\n",0,0) ;
				smt_send_rdf(smc,mb,m_fc(mb),SMT_RDF_LENGTH,
					local) ;
				break ;
			}
			DB_SMT("SMT - sending ECF reply to %s\n",
				addr_to_string(&sm->smt_source),0) ;

			/* set destination addr.  & reply */
			sm->smt_dest = sm->smt_source ;
			sm->smt_type = SMT_REPLY ;
			dump_smt(smc,sm,"ECF REPLY") ;
			smc->mib.priv.fddiPRIVECF_Reply_Tx++ ;
			smt_send_frame(smc,mb,FC_SMT_INFO,local) ;
			return ;		/* DON'T free mbuf */
			}
		default :
			illegal = 1 ;
			break ;
		}
		break ;
#ifndef	BOOT
	case SMT_RAF :		/* resource allocation */
#ifdef	ESS
		DB_ESSN(2,"ESS: RAF frame received\n",0,0) ;
		fs = ess_raf_received_pack(smc,mb,sm,fs) ;
#endif

#ifdef	SBA
		DB_SBAN(2,"SBA: RAF frame received\n",0,0) ;
		sba_raf_received_pack(smc,sm,fs) ;
#endif
		break ;
	case SMT_RDF :		/* request denied */
		smc->mib.priv.fddiPRIVRDF_Rx++ ;
		break ;
	case SMT_ESF :		/* extended service - not supported */
		if (sm->smt_type == SMT_REQUEST) {
			DB_SMT("SMT - received ESF, sending RDF\n",0,0) ;
			smt_send_rdf(smc,mb,m_fc(mb),SMT_RDF_CLASS,local) ;
		}
		break ;
	case SMT_PMF_GET :
	case SMT_PMF_SET :
		if (sm->smt_type != SMT_REQUEST)
			break ;
		/* update statistics */
		if (sm->smt_class == SMT_PMF_GET)
			smc->mib.priv.fddiPRIVPMF_Get_Rx++ ;
		else
			smc->mib.priv.fddiPRIVPMF_Set_Rx++ ;
		/*
		 * ignore PMF SET with I/G set
		 */
		if ((sm->smt_class == SMT_PMF_SET) &&
			!is_individual(&sm->smt_dest)) {
			DB_SMT("SMT: ignoring PMF-SET with I/G set\n",0,0) ;
			break ;
		}
		smt_pmf_received_pack(smc,mb, local) ;
		break ;
	case SMT_SRF :
		dump_smt(smc,sm,"SRF received") ;
		break ;
	default :
		if (sm->smt_type != SMT_REQUEST)
			break ;
		/*
		 * For frames with unknown class:
		 * we need to send a RDF frame according to 8.1.3.1.1,
		 * only if it is a REQUEST.
		 */
		DB_SMT("SMT : class = %d, send RDF to %s\n",
			sm->smt_class, addr_to_string(&sm->smt_source)) ;

		smt_send_rdf(smc,mb,m_fc(mb),SMT_RDF_CLASS,local) ;
		break ;
#endif
	}
