#if	0
if (smc->debug.d_plc & 0x80)
#else
	if (debug.d_plc & 0x80)
#endif
		printf("SIGNALING bit %d .. %d\n",phy->bitn,phy->bitn+len-1) ;
