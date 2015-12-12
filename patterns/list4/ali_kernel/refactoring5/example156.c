#ifdef DOT11_N_SUPPORT
if (pRxBlk->pRxWI->PHYMODE >= MODE_HTMIX)
    {
	rate_index = 16 + ((UCHAR)pRxBlk->pRxWI->BW *16) + ((UCHAR)pRxBlk->pRxWI->ShortGI *32) + ((UCHAR)pRxBlk->pRxWI->MCS);
    }
    else
#endif // DOT11_N_SUPPORT //
	if (pRxBlk->pRxWI->PHYMODE == MODE_OFDM)
	rate_index = (UCHAR)(pRxBlk->pRxWI->MCS) + 4;
    else
	rate_index = (UCHAR)(pRxBlk->pRxWI->MCS);
