#ifndef	PCI
if (inpw(CSR_A) & CS_SAS)
#else
	if (!(inp(ADDR(B0_DAS)) & DAS_AVAIL))
#endif
		smc->s.sas = SMT_SAS ;	/* Single att. station */
	else
		smc->s.sas = SMT_DAS ;
