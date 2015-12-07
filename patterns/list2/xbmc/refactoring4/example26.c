#ifdef MNG_INCLUDE_JNG
if ((pData->bHasIDAT) || (pData->bHasPLTE) || (pData->bHasJDAT) || (pData->bHasJDAA))
#else
  if ((pData->bHasIDAT) || (pData->bHasPLTE))
#endif
    MNG_ERROR (pData, MNG_SEQUENCEERROR);
