switch (smc->s.sas) {
#ifdef	CONCENTRATOR
		case SMT_SAS :
			mib->fddiPORTMy_Type = (np == PS) ? TS : TM ;
			break ;
		case SMT_DAS :
			mib->fddiPORTMy_Type = (np == PA) ? TA :
					(np == PB) ? TB : TM ;
			break ;
		case SMT_NAC :
			mib->fddiPORTMy_Type = TM ;
			break;
#else
		case SMT_SAS :
			mib->fddiPORTMy_Type = (np == PS) ? TS : TNONE ;
			mib->fddiPORTHardwarePresent = (np == PS) ? TRUE :
					FALSE ;
#ifndef	SUPERNET_3
			smc->y[PA].mib->fddiPORTPCMState = PC0_OFF ;
#else
			smc->y[PB].mib->fddiPORTPCMState = PC0_OFF ;
#endif
			break ;
		case SMT_DAS :
			mib->fddiPORTMy_Type = (np == PB) ? TB : TA ;
			break ;
#endif
		}
