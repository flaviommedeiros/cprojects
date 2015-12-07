#ifdef AGGREGATION_SUPPORT
if ((pRxWI->PHYMODE <= MODE_OFDM)
		    && (OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_AGGREGATION_INUSED)))
		{
			RX_BLK_SET_FLAG(pRxBlk, fRX_ARALINK);
		} else
#endif /* AGGREGATION_SUPPORT // */
		{
			RX_BLK_SET_FLAG(pRxBlk, fRX_HTC);
			/* skip HTC contorl field */
			pRxBlk->pData += 4;
			pRxBlk->DataSize -= 4;
		}
