switch (smc->s.sas) {
		case SMT_DAS :
			/*
			 * MAC intended on output
			 */
			if (phy->pc_mode == PM_TREE) {
				if ((np == PB) || ((np == PA) &&
				(smc->y[PB].mib->fddiPORTConnectState !=
					PCM_ACTIVE)))
					phy->t_val[9] = TRUE ;
			}
			else {
				if (np == PB)
					phy->t_val[9] = TRUE ;
			}
			break ;
		case SMT_SAS :
			if (np == PS)
				phy->t_val[9] = TRUE ;
			break ;
#ifdef	CONCENTRATOR
		case SMT_NAC :
			/*
			 * MAC intended on output
			 */
			if (np == PB)
				phy->t_val[9] = TRUE ;
			break ;
#endif
		}
