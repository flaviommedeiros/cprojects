switch (pa->p_type) {
	case SMT_P101A:			/* fddiSMTConfigPolicy */
		if (word_val & ~1)
			goto val_error ;
		IFSET(mib->fddiSMTConfigPolicy = word_val) ;
		break ;
	case SMT_P101B :		/* fddiSMTConnectionPolicy */
		if (!(word_val & POLICY_MM))
			goto val_error ;
		IFSET(mib->fddiSMTConnectionPolicy = word_val) ;
		break ;
	case SMT_P101D : 		/* fddiSMTTT_Notify */
		if (word_val < 2 || word_val > 30)
			goto val_error ;
		IFSET(mib->fddiSMTTT_Notify = word_val) ;
		break ;
	case SMT_P101E :		/* fddiSMTStatRptPolicy */
		if (byte_val & ~1)
			goto val_error ;
		IFSET(mib->fddiSMTStatRptPolicy = byte_val) ;
		break ;
	case SMT_P101F :		/* fddiSMTTrace_MaxExpiration */
		/*
		 * note: lower limit trace_max = 6.001773... s
		 * NO upper limit
		 */
		if (long_val < (long)0x478bf51L)
			goto val_error ;
		IFSET(mib->fddiSMTTrace_MaxExpiration = long_val) ;
		break ;
#ifdef	ESS
	case SMT_P10F2 :		/* fddiESSPayload */
		if (long_val > 1562)
			goto val_error ;
		if (set && smc->mib.fddiESSPayload != long_val) {
			smc->ess.raf_act_timer_poll = TRUE ;
			smc->mib.fddiESSPayload = long_val ;
		}
		break ;
	case SMT_P10F3 :		/* fddiESSOverhead */
		if (long_val < 50 || long_val > 5000)
			goto val_error ;
		if (set && smc->mib.fddiESSPayload &&
			smc->mib.fddiESSOverhead != long_val) {
			smc->ess.raf_act_timer_poll = TRUE ;
			smc->mib.fddiESSOverhead = long_val ;
		}
		break ;
	case SMT_P10F4 :		/* fddiESSMaxTNeg */
		if (long_val > -MS2BCLK(5) || long_val < -MS2BCLK(165))
			goto val_error ;
		IFSET(mib->fddiESSMaxTNeg = long_val) ;
		break ;
	case SMT_P10F5 :		/* fddiESSMinSegmentSize */
		if (long_val < 1 || long_val > 4478)
			goto val_error ;
		IFSET(mib->fddiESSMinSegmentSize = long_val) ;
		break ;
	case SMT_P10F6 :		/* fddiESSCategory */
		if ((long_val & 0xffff) != 1)
			goto val_error ;
		IFSET(mib->fddiESSCategory = long_val) ;
		break ;
	case SMT_P10F7 :		/* fddiESSSyncTxMode */
		if (word_val > 1)
			goto val_error ;
		IFSET(mib->fddiESSSynchTxMode = word_val) ;
		break ;
#endif
#ifdef	SBA
	case SMT_P10F8 :		/* fddiSBACommand */
		if (byte_val != SB_STOP && byte_val != SB_START)
			goto val_error ;
		IFSET(mib->fddiSBACommand = byte_val) ;
		break ;
	case SMT_P10F9 :		/* fddiSBAAvailable */
		if (byte_val > 100)
			goto val_error ;
		IFSET(mib->fddiSBAAvailable = byte_val) ;
		break ;
#endif
	case SMT_P2020 :		/* fddiMACRequestedPaths */
		if ((word_val & (MIB_P_PATH_PRIM_PREFER |
			MIB_P_PATH_PRIM_ALTER)) == 0 )
			goto val_error ;
		IFSET(mib_m->fddiMACRequestedPaths = word_val) ;
		break ;
	case SMT_P205F :		/* fddiMACFrameErrorThreshold */
		/* 0 .. ffff acceptable */
		IFSET(mib_m->fddiMACFrameErrorThreshold = word_val) ;
		break ;
	case SMT_P2067 :		/* fddiMACNotCopiedThreshold */
		/* 0 .. ffff acceptable */
		IFSET(mib_m->fddiMACNotCopiedThreshold = word_val) ;
		break ;
	case SMT_P2076:			/* fddiMACMA_UnitdataEnable */
		if (byte_val & ~1)
			goto val_error ;
		if (set) {
			mib_m->fddiMACMA_UnitdataEnable = byte_val ;
			queue_event(smc,EVENT_RMT,RM_ENABLE_FLAG) ;
		}
		break ;
	case SMT_P20F1 :		/* fddiMACT_Min */
		IFSET(mib_m->fddiMACT_Min = long_val) ;
		break ;
	case SMT_P320F :
		if (long_val > 1562)
			goto val_error ;
		IFSET(mib_a->fddiPATHSbaPayload = long_val) ;
#ifdef	ESS
		if (set)
			ess_para_change(smc) ;
#endif
		break ;
	case SMT_P3210 :
		if (long_val > 5000)
			goto val_error ;
		
		if (long_val != 0 && mib_a->fddiPATHSbaPayload == 0)
			goto val_error ;

		IFSET(mib_a->fddiPATHSbaOverhead = long_val) ;
#ifdef	ESS
		if (set)
			ess_para_change(smc) ;
#endif
		break ;
	case SMT_P3213:			/* fddiPATHT_Rmode */
		/* no limit :
		 * 0 .. 343.597 => 0 .. 2e32 * 80nS
		 */
		if (set) {
			mib_a->fddiPATHT_Rmode = long_val ;
			rtm_set_timer(smc) ;
		}
		break ;
	case SMT_P3214 :		/* fddiPATHSbaAvailable */
		if (long_val > 0x00BEBC20L)
			goto val_error ;
#ifdef SBA 
		if (set && mib->fddiSBACommand == SB_STOP)
			goto val_error ;
#endif
		IFSET(mib_a->fddiPATHSbaAvailable = long_val) ;
		break ;
	case SMT_P3215 :		/* fddiPATHTVXLowerBound */
		IFSET(mib_a->fddiPATHTVXLowerBound = long_val) ;
		goto change_mac_para ;
	case SMT_P3216 :		/* fddiPATHT_MaxLowerBound */
		IFSET(mib_a->fddiPATHT_MaxLowerBound = long_val) ;
		goto change_mac_para ;
	case SMT_P3217 :		/* fddiPATHMaxT_Req */
		IFSET(mib_a->fddiPATHMaxT_Req = long_val) ;

change_mac_para:
		if (set && smt_set_mac_opvalues(smc)) {
			RS_SET(smc,RS_EVENT) ;
			smc->sm.please_reconnect = 1 ;
			queue_event(smc,EVENT_ECM,EC_DISCONNECT) ;
		}
		break ;
	case SMT_P400E :		/* fddiPORTConnectionPolicies */
		if (byte_val > 1)
			goto val_error ;
		IFSET(mib_p->fddiPORTConnectionPolicies = byte_val) ;
		break ;
	case SMT_P4011 :		/* fddiPORTRequestedPaths */
		/* all 3*8 bits allowed */
		IFSET(memcpy((char *)mib_p->fddiPORTRequestedPaths,
			(char *)&long_val,4)) ;
		break ;
	case SMT_P401F:			/* fddiPORTMaint_LS */
		if (word_val > 4)
			goto val_error ;
		IFSET(mib_p->fddiPORTMaint_LS = word_val) ;
		break ;
	case SMT_P403A :		/* fddiPORTLer_Cutoff */
		if (byte_val < 4 || byte_val > 15)
			goto val_error ;
		IFSET(mib_p->fddiPORTLer_Cutoff = byte_val) ;
		break ;
	case SMT_P403B :		/* fddiPORTLer_Alarm */
		if (byte_val < 4 || byte_val > 15)
			goto val_error ;
		IFSET(mib_p->fddiPORTLer_Alarm = byte_val) ;
		break ;

	/*
	 * Actions
	 */
	case SMT_P103C :		/* fddiSMTStationAction */
		if (smt_action(smc,SMT_STATION_ACTION, (int) word_val, 0))
			goto val_error ;
		break ;
	case SMT_P4046:			/* fddiPORTAction */
		if (smt_action(smc,SMT_PORT_ACTION, (int) word_val,
			port_to_mib(smc,port)))
			goto val_error ;
		break ;
	default :
		break ;
	}
