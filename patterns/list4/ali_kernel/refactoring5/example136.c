#ifdef CONFIG_STA_SUPPORT
if ((IS_RT3090(pAd) || IS_RT3572(pAd) || IS_RT3390(pAd)) && IS_VERSION_AFTER_F(pAd)
				&& (pAd->StaCfg.PSControl.field.rt30xxPowerMode == 3)
				&& (pAd->StaCfg.PSControl.field.EnableNewPS == TRUE))
				{
							PsPollTime -= 5;
				}
				else
#endif // CONFIG_STA_SUPPORT //
#endif // PCIE_PS_SUPPORT //
				PsPollTime -= 3;
