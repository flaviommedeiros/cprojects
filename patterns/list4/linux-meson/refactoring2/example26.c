#ifdef CONFIG_LOAD_PHY_PARA_FROM_FILE
if (rtStatus == _FAIL)
#endif
	{
#ifdef CONFIG_EMBEDDED_FWIMG
		ODM_ConfigMACWithHeaderFile(&pHalData->odmpriv);
		rtStatus = _SUCCESS;
#endif//CONFIG_EMBEDDED_FWIMG
	}
