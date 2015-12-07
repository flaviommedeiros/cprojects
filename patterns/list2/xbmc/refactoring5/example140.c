#ifdef FILTER193
if (pData->iFilter == 0xC1)          /* no adaptive filtering ? */
    pData->iPixelofs = pData->iFilterofs;
  else
#endif
    pData->iPixelofs = pData->iFilterofs + 1;
