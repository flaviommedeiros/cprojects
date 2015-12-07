#ifdef RTMP_MAC_PCI
if (bUseDataQ) {
				Status =
				    MlmeDataHardTransmit(pAd, QueIdx, pPacket);
				retryCnt--;
			} else
#endif /* RTMP_MAC_PCI // */
				Status = MlmeHardTransmit(pAd, QueIdx, pPacket);
