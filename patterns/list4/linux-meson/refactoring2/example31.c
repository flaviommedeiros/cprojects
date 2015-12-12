#ifdef CONFIG_LOAD_PHY_PARA_FROM_FILE
if (phy_ConfigBBWithParaFile(Adapter, pszAGCTableFile, CONFIG_BB_AGC_TAB) == _FAIL)
#endif
	{
#ifdef CONFIG_EMBEDDED_FWIMG
		if (HAL_STATUS_SUCCESS != ODM_ConfigBBWithHeaderFile(&pHalData->odmpriv, CONFIG_BB_AGC_TAB))
			rtStatus = _FAIL;
#endif
	}
