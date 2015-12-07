#ifdef RT3070
if ((IS_RT3070(pAd) && ((pAd->MACVersion & 0xffff) < 0x0201)))
#endif /* RT3070 // */
		{
			if ((pAd->StaCfg.RssiSample.AvgRssi0 != 0)
			    && (pAd->StaCfg.RssiSample.AvgRssi0 >
				(pAd->BbpRssiToDbmDelta - 35))) {
				RT30xxWriteRFRegister(pAd, RF_R27, 0x20);
			} else {
				RT30xxWriteRFRegister(pAd, RF_R27, 0x23);
			}
		}
