#ifdef RT2860
if ( pAd->MACVersion == 0x28600100 )
		return MlmeHardTransmitTxRing(pAd,QueIdx,pPacket);
	else
#endif
		return MlmeHardTransmitMgmtRing(pAd,QueIdx,pPacket);
