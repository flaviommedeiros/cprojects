switch (pTxBlk->TxFrameType)
	{
#ifdef DOT11_N_SUPPORT
		case TX_AMPDU_FRAME:
				STA_AMPDU_Frame_Tx(pAd, pTxBlk);
			break;
		case TX_AMSDU_FRAME:
				STA_AMSDU_Frame_Tx(pAd, pTxBlk);
			break;
#endif // DOT11_N_SUPPORT //
		case TX_LEGACY_FRAME:
				STA_Legacy_Frame_Tx(pAd, pTxBlk);
			break;
		case TX_MCAST_FRAME:
				STA_Legacy_Frame_Tx(pAd, pTxBlk);
			break;
		case TX_RALINK_FRAME:
				STA_ARalink_Frame_Tx(pAd, pTxBlk);
			break;
		case TX_FRAG_FRAME:
				STA_Fragment_Frame_Tx(pAd, pTxBlk);
			break;
		default:
			{
				// It should not happened!
				DBGPRINT(RT_DEBUG_ERROR, ("Send a pacekt was not classified!! It should not happen!\n"));
				while(pTxBlk->TxPacketList.Number)
				{
					pQEntry = RemoveHeadQueue(&pTxBlk->TxPacketList);
					pPacket = QUEUE_ENTRY_TO_PACKET(pQEntry);
					if (pPacket)
						RELEASE_NDIS_PACKET(pAd, pPacket, NDIS_STATUS_FAILURE);
				}
			}
			break;
	}
