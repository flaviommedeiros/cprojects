switch(class = ev->class) {
		case EVENT_ECM :		/* Entity Corordination  Man. */
			ecm(smc,(int)ev->event) ;
			break ;
		case EVENT_CFM :		/* Configuration Man. */
			cfm(smc,(int)ev->event) ;
			break ;
		case EVENT_RMT :		/* Ring Man. */
			rmt(smc,(int)ev->event) ;
			break ;
		case EVENT_SMT :
			smt_event(smc,(int)ev->event) ;
			break ;
#ifdef	CONCENTRATOR
		case 99 :
			timer_test_event(smc,(int)ev->event) ;
			break ;
#endif
		case EVENT_PCMA :		/* PHY A */
		case EVENT_PCMB :		/* PHY B */
		default :
			if (class >= EVENT_PCMA &&
			    class < EVENT_PCMA + NUMPHYS) {
				pcm(smc,class - EVENT_PCMA,(int)ev->event) ;
				break ;
			}
			SMT_PANIC(smc,SMT_E0121, SMT_E0121_MSG) ;
			return ;
		}
