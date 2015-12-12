#ifdef MULTIPLE_CARD_SUPPORT
if (pAd->MC_RowID >= 0)
			sprintf(suffixName, "%02d_%d", pAd->MC_RowID, ifNameIdx);
		else
#endif // MULTIPLE_CARD_SUPPORT //
		sprintf(suffixName, "%d", ifNameIdx);
