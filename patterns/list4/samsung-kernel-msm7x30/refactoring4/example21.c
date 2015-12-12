#ifdef	MOT_ELM
if (!(inpw(PLC(np,PL_STATUS_B)) & PL_PCM_SIGNAL))
#else	/* nMOT_ELM */
		if (((inpw(PLC(np,PL_STATUS_A)) & PLC_REV_MASK) !=
			PLC_REVISION_A) &&
			!(inpw(PLC(np,PL_STATUS_B)) & PL_PCM_SIGNAL))
#endif	/* nMOT_ELM */
		{
			/*
			 * Set register again (PLCS errata) or the first time
			 * (new SN3 PLCS).
			 */
			(void) plc_send_bits(smc,phy,3) ;
		}
