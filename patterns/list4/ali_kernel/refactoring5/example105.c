#ifdef QOS_DLS_SUPPORT
if (!pAd->CommonCfg.bDLSCapable)
	    {
#endif // QOS_DLS_SUPPORT //
		if (INFRA_ON(pAd))
		{
			// Infrastructure mode, check address 2 for BSSID
			if (!RTMPEqualMemory(&pHeader->Addr2, &pAd->CommonCfg.Bssid, 6))
			{
				// Receive frame not my BSSID
	            // release packet
	            RELEASE_NDIS_PACKET(pAd, pRxPacket, NDIS_STATUS_FAILURE);
				return;
			}
		}
		else	// Ad-Hoc mode or Not associated
		{
			// Ad-Hoc mode, check address 3 for BSSID
			if (!RTMPEqualMemory(&pHeader->Addr3, &pAd->CommonCfg.Bssid, 6))
			{
				// Receive frame not my BSSID
	            // release packet
	            RELEASE_NDIS_PACKET(pAd, pRxPacket, NDIS_STATUS_FAILURE);
				return;
			}
		}
#ifdef QOS_DLS_SUPPORT
	    }
