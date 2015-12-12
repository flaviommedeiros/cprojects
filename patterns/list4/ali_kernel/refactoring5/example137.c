#ifdef RTMP_MAC_PCI
if (bUseDataQ)
		{
			retryCnt = MAX_DATAMM_RETRY;
			// free Tx(QueIdx) resources
			RTMPFreeTXDUponTxDmaDone(pAd, QueIdx);
			FreeNum = GET_TXRING_FREENO(pAd, QueIdx);
		}
		else
#endif // RTMP_MAC_PCI //
		{
			FreeNum = GET_MGMTRING_FREENO(pAd);
		}
