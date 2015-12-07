#ifdef RTMP_MAC_PCI
if (pAd->MACVersion == 0x28600100)
		return MlmeHardTransmitTxRing(pAd, QueIdx, pPacket);
	else
#endif /* RTMP_MAC_PCI // */
		return MlmeHardTransmitMgmtRing(pAd, QueIdx, pPacket);
