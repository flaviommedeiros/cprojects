if (((pAd->StaCfg.AuthMode == Ndis802_11AuthModeWPA) ||
		 (pAd->StaCfg.AuthMode == Ndis802_11AuthModeWPAPSK) ||
		 (pAd->StaCfg.AuthMode == Ndis802_11AuthModeWPA2) ||
		 (pAd->StaCfg.AuthMode == Ndis802_11AuthModeWPA2PSK)
#ifdef WPA_SUPPLICANT_SUPPORT
		  || (pAd->StaCfg.IEEE8021X == TRUE)
#endif // WPA_SUPPLICANT_SUPPORT //
		  )
		  && ((pAd->StaCfg.PortSecured == WPA_802_1X_PORT_NOT_SECURED) || (pAd->StaCfg.MicErrCnt >= 2))
		  && (RTMP_GET_PACKET_EAPOL(pPacket)== FALSE)
		  )
	{
		DBGPRINT(RT_DEBUG_TRACE,("STASendPacket --> Drop packet before port secured !!!\n"));
		RELEASE_NDIS_PACKET(pAd, pPacket, NDIS_STATUS_FAILURE);

		return (NDIS_STATUS_FAILURE);
	}
