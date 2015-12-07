#ifndef	MOT_ELM
if (rev != PLC_REVISION_A)
#endif	/* MOT_ELM */
	{
		if (smc->y[p].pmd_scramble) {
			outpw(PLC(p,PL_CNTRL_C),PLCS_CONTROL_C_S) ;
#ifdef	MOT_ELM
			outpw(PLC(p,PL_T_FOT_ASS),PLCS_FASSERT_S) ;
			outpw(PLC(p,PL_T_FOT_DEASS),PLCS_FDEASSERT_S) ;
#endif	/* MOT_ELM */
		}
		else {
			outpw(PLC(p,PL_CNTRL_C),PLCS_CONTROL_C_U) ;
#ifdef	MOT_ELM
			outpw(PLC(p,PL_T_FOT_ASS),PLCS_FASSERT_U) ;
			outpw(PLC(p,PL_T_FOT_DEASS),PLCS_FDEASSERT_U) ;
#endif	/* MOT_ELM */
		}
	}
