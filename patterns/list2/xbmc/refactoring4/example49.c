#ifdef MNG_INCLUDE_JNG
if ((pData->bHasPLTE) || (pData->bHasIDAT) || (pData->bHasJDAT) || (pData->bHasJDAA))
#else
  if ((pData->bHasPLTE) || (pData->bHasIDAT))
#endif
    MNG_ERROR (pData, MNG_SEQUENCEERROR);
