#ifdef DOT11_N_SUPPORT
if (RX_BLK_TEST_FLAG(pRxBlk, fRX_AMSDU))
		{
			// handle A-MSDU
			Indicate_AMSDU_Packet(pAd, pRxBlk, FromWhichBSSID);
		}
		else
#endif // DOT11_N_SUPPORT //
		{
			Indicate_Legacy_Packet(pAd, pRxBlk, FromWhichBSSID);
		}
