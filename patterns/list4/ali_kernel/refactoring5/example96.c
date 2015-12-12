#ifdef RT2860
if ((pAd->OpMode == OPMODE_STA) &&
				(pAd->StaCfg.BssType == BSS_ADHOC))
				pEntry->PortSecured = WPA_802_1X_PORT_SECURED;
			else
#endif
			pEntry->PortSecured = WPA_802_1X_PORT_NOT_SECURED;
