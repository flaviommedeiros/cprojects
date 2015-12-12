switch(Elem->MsgType)
	{
		case OID_802_11_SSID:
			CntlOidSsidProc(pAd, Elem);
			break;

		case OID_802_11_BSSID:
			CntlOidRTBssidProc(pAd,Elem);
			break;

		case OID_802_11_BSSID_LIST_SCAN:
			CntlOidScanProc(pAd,Elem);
			break;

		case OID_802_11_DISASSOCIATE:
			DisassocParmFill(pAd, &DisassocReq, pAd->CommonCfg.Bssid, REASON_DISASSOC_STA_LEAVING);
			MlmeEnqueue(pAd, ASSOC_STATE_MACHINE, MT2_MLME_DISASSOC_REQ, sizeof(MLME_DISASSOC_REQ_STRUCT), &DisassocReq);
			pAd->Mlme.CntlMachine.CurrState = CNTL_WAIT_OID_DISASSOC;
#ifdef WPA_SUPPLICANT_SUPPORT
            if (pAd->StaCfg.WpaSupplicantUP != WPA_SUPPLICANT_ENABLE_WITH_WEB_UI)
#endif // WPA_SUPPLICANT_SUPPORT //
            {
			// Set the AutoReconnectSsid to prevent it reconnect to old SSID
			// Since calling this indicate user don't want to connect to that SSID anymore.
			pAd->MlmeAux.AutoReconnectSsidLen= 32;
			NdisZeroMemory(pAd->MlmeAux.AutoReconnectSsid, pAd->MlmeAux.AutoReconnectSsidLen);
            }
			break;

		case MT2_MLME_ROAMING_REQ:
			CntlMlmeRoamingProc(pAd, Elem);
			break;

        case OID_802_11_MIC_FAILURE_REPORT_FRAME:
            WpaMicFailureReportFrame(pAd, Elem);
            break;

#ifdef QOS_DLS_SUPPORT
		case RT_OID_802_11_SET_DLS_PARAM:
			CntlOidDLSSetupProc(pAd, Elem);
			break;
#endif // QOS_DLS_SUPPORT //

		default:
			DBGPRINT(RT_DEBUG_TRACE, ("CNTL - Illegal message in CntlIdleProc(MsgType=%ld)\n",Elem->MsgType));
			break;
	}
