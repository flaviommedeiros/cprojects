#ifdef DOT11_N_SUPPORT
if (((pAd->StaCfg.WepStatus != Ndis802_11WEPEnabled) && (pAd->StaCfg.WepStatus != Ndis802_11Encryption2Enabled))
				|| (pAd->CommonCfg.HT_DisallowTKIP == FALSE))
			{
				bAllowNrate = TRUE;
			}
