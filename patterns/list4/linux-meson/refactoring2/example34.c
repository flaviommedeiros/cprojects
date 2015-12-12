#ifdef CONFIG_LOAD_PHY_PARA_FROM_FILE
if (PHY_ConfigRFWithTxPwrTrackParaFile(Adapter, pszTxPwrTrackFile) == _FAIL)
#endif
	{
#ifdef CONFIG_EMBEDDED_FWIMG
		ODM_ConfigRFWithTxPwrTrackHeaderFile(&pHalData->odmpriv);
#endif
	}
