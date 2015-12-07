#if !defined(BCMBUSTYPE) || (BCMBUSTYPE == SI_BUS)
if (sii != &ksii)
#endif	/* !BCMBUSTYPE || (BCMBUSTYPE == SI_BUS) */
		MFREE(sii->osh, sii, sizeof(si_info_t));
