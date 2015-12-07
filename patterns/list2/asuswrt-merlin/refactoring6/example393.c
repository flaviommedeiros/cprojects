if ( (stu & (FM_SXMTABT |		/* transmit abort */
#ifdef	SYNC
		     FM_STXABRS |	/* syn. tx abort */
#endif	/* SYNC */
		     FM_STXABRA0)) ||	/* asyn. tx abort */
	     (stl & (FM_SQLCKS |		/* lock for syn. q. */
		     FM_SQLCKA0)) ) {	/* lock for asyn. q. */
		formac_tx_restart(smc) ;		/* init tx */
		restart_tx = 1 ;
		stu = inpw(FM_A(FM_ST1U)) ;
		stl = inpw(FM_A(FM_ST1L)) ;
		stu &= ~ (FM_STECFRMA0 | FM_STEFRMA0 | FM_STEFRMS) ;
		if (stu || stl)
			goto again ;
	}
