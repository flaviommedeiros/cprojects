#ifdef QOS_DLS_SUPPORT
if ((pHeader->FC.FrDs == 0) && (pHeader->FC.ToDs == 0))
				RX_BLK_SET_FLAG(pRxBlk, fRX_DLS);
			else
#endif // QOS_DLS_SUPPORT //
			ASSERT(pRxWI->WirelessCliID == BSSID_WCID);
