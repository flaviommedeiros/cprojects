#ifdef PCIE_PS_SUPPORT
if (!(((IS_RT3090(pAd) || IS_RT3572(pAd) || IS_RT3390(pAd)) && IS_VERSION_AFTER_F(pAd)
	&& (pAd->StaCfg.PSControl.field.rt30xxPowerMode == 3)
	&& (pAd->StaCfg.PSControl.field.EnableNewPS == TRUE))))
#endif // PCIE_PS_SUPPORT //
	{
    pAd->bPCIclkOff = FALSE;
		DBGPRINT(RT_DEBUG_TRACE, ("PSM :309xbPCIclkOff == %d\n", pAd->bPCIclkOff));

	}
