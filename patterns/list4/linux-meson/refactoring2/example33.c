#ifdef CONFIG_EMBEDDED_FWIMG
if(HAL_STATUS_FAILURE ==ODM_ConfigRFWithHeaderFile(&pHalData->odmpriv,CONFIG_RF_RADIO, (ODM_RF_RADIO_PATH_E)eRFPath))
					rtStatus = _FAIL;
