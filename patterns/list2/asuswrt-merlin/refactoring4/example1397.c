#ifndef	PCI
if (inpw(CSR_A) & CS_BYSTAT)
#else
	if (!(inp(ADDR(B0_DAS)) & DAS_BYP_ST))
#endif
		smc->mib.fddiSMTBypassPresent = 0 ;
		/* without opt. bypass */
	else
		smc->mib.fddiSMTBypassPresent = 1 ;
