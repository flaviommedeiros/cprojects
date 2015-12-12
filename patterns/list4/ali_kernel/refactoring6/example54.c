if (OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_PCIE_DEVICE)
		&& pAd->OpMode == OPMODE_STA
#ifdef CONFIG_STA_SUPPORT
		&&pAd->StaCfg.PSControl.field.EnableNewPS == TRUE
#endif // CONFIG_STA_SUPPORT //
		)
	{

	    RTMPCancelTimer(&pAd->Mlme.RadioOnOffTimer,	&Cancelled);
	    RTMPCancelTimer(&pAd->Mlme.PsPollTimer,	&Cancelled);

	    if (Level == DOT11POWERSAVE)
		{
			RTMP_IO_READ32(pAd, TBTT_TIMER, &TbTTTime);
			TbTTTime &= 0x1ffff;
			// 00. check if need to do sleep in this DTIM period.   If next beacon will arrive within 30ms , ...doesn't necessarily sleep.
			// TbTTTime uint = 64us, LEAD_TIME unit = 1024us, PsPollTime unit = 1ms
	        if  (((64*TbTTTime) <((LEAD_TIME*1024) + 40000)) && (TbttNumToNextWakeUp == 0))
			{
				DBGPRINT(RT_DEBUG_TRACE, ("TbTTTime = 0x%x , give up this sleep. \n", TbTTTime));
	            OPSTATUS_CLEAR_FLAG(pAd, fOP_STATUS_DOZE);
	            //pAd->bPCIclkOffDisableTx = FALSE;
	            RTMP_CLEAR_PSFLAG(pAd, fRTMP_PS_DISABLE_TX);
				return FALSE;
			}
			else
			{
				PsPollTime = (64*TbTTTime- LEAD_TIME*1024)/1000;
#ifdef PCIE_PS_SUPPORT
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

	            BeaconPeriodTime = pAd->CommonCfg.BeaconPeriod*102/100;
				if (TbttNumToNextWakeUp > 0)
					PsPollTime += ((TbttNumToNextWakeUp -1) * BeaconPeriodTime);

	            pAd->Mlme.bPsPollTimerRunning = TRUE;
				RTMPSetTimer(&pAd->Mlme.PsPollTimer, PsPollTime);
			}
		}
	}
	else
	{
		DBGPRINT(RT_DEBUG_TRACE, ("RT28xxPciAsicRadioOff::Level!=DOT11POWERSAVE \n"));
	}
