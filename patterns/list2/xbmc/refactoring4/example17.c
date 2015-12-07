#ifdef MNG_SUPPORT_TRACE
if ((!pData->bHasIHDR) && (!pData->bHasBASI) && (!pData->bHasDHDR) && (!pData->bHasJHDR))
#else
  if ((!pData->bHasIHDR) && (!pData->bHasBASI) && (!pData->bHasDHDR))
#endif
    MNG_ERROR (pData, MNG_SEQUENCEERROR);
