#ifdef CONFIG_LOAD_PHY_PARA_FROM_FILE
if (PHY_ConfigRFWithPowerLimitTableParaFile( Adapter, pszRFTxPwrLmtFile )== _FAIL)
#endif
		{
#ifdef CONFIG_EMBEDDED_FWIMG
			if (HAL_STATUS_SUCCESS != ODM_ConfigRFWithHeaderFile(&pHalData->odmpriv, CONFIG_RF_TXPWR_LMT, (ODM_RF_RADIO_PATH_E)0))
				rtStatus = _FAIL;
#endif
		}
