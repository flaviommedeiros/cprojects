#ifdef RT2860
if (RTMPGetKeyParameter("PSMode", tmpbuf, 32, buffer))
#endif
#ifdef RT2870
						if (RTMPGetKeyParameter("PSMode", tmpbuf, 10, buffer))
#endif
						{
							if (pAd->StaCfg.BssType == BSS_INFRA)
							{
								if ((strcmp(tmpbuf, "MAX_PSP") == 0) || (strcmp(tmpbuf, "max_psp") == 0))
								{
									// do NOT turn on PSM bit here, wait until MlmeCheckForPsmChange()
									// to exclude certain situations.
									//	   MlmeSetPsm(pAd, PWR_SAVE);
									OPSTATUS_SET_FLAG(pAd, fOP_STATUS_RECEIVE_DTIM);
									if (pAd->StaCfg.bWindowsACCAMEnable == FALSE)
										pAd->StaCfg.WindowsPowerMode = Ndis802_11PowerModeMAX_PSP;
									pAd->StaCfg.WindowsBatteryPowerMode = Ndis802_11PowerModeMAX_PSP;
									pAd->StaCfg.DefaultListenCount = 5;
								}
								else if ((strcmp(tmpbuf, "Fast_PSP") == 0) || (strcmp(tmpbuf, "fast_psp") == 0)
									|| (strcmp(tmpbuf, "FAST_PSP") == 0))
								{
									// do NOT turn on PSM bit here, wait until MlmeCheckForPsmChange()
									// to exclude certain situations.
									//	   MlmeSetPsmBit(pAd, PWR_SAVE);
									OPSTATUS_SET_FLAG(pAd, fOP_STATUS_RECEIVE_DTIM);
									if (pAd->StaCfg.bWindowsACCAMEnable == FALSE)
										pAd->StaCfg.WindowsPowerMode = Ndis802_11PowerModeFast_PSP;
									pAd->StaCfg.WindowsBatteryPowerMode = Ndis802_11PowerModeFast_PSP;
									pAd->StaCfg.DefaultListenCount = 3;
								}
								else if ((strcmp(tmpbuf, "Legacy_PSP") == 0) || (strcmp(tmpbuf, "legacy_psp") == 0)
									|| (strcmp(tmpbuf, "LEGACY_PSP") == 0))
								{
									// do NOT turn on PSM bit here, wait until MlmeCheckForPsmChange()
									// to exclude certain situations.
									//	   MlmeSetPsmBit(pAd, PWR_SAVE);
									OPSTATUS_SET_FLAG(pAd, fOP_STATUS_RECEIVE_DTIM);
									if (pAd->StaCfg.bWindowsACCAMEnable == FALSE)
										pAd->StaCfg.WindowsPowerMode = Ndis802_11PowerModeLegacy_PSP;
									pAd->StaCfg.WindowsBatteryPowerMode = Ndis802_11PowerModeLegacy_PSP;
									pAd->StaCfg.DefaultListenCount = 3;
								}
								else
								{ //Default Ndis802_11PowerModeCAM
									// clear PSM bit immediately
									MlmeSetPsmBit(pAd, PWR_ACTIVE);
									OPSTATUS_SET_FLAG(pAd, fOP_STATUS_RECEIVE_DTIM);
									if (pAd->StaCfg.bWindowsACCAMEnable == FALSE)
										pAd->StaCfg.WindowsPowerMode = Ndis802_11PowerModeCAM;
									pAd->StaCfg.WindowsBatteryPowerMode = Ndis802_11PowerModeCAM;
								}
								DBGPRINT(RT_DEBUG_TRACE, ("PSMode=%ld\n", pAd->StaCfg.WindowsPowerMode));
							}
						}
