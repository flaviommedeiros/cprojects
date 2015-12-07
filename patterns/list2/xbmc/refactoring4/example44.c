#ifdef MNG_INCLUDE_JNG
if ((pData->bHasIDAT) || (pData->bHasJDAT) || (pData->bHasJDAA))
#else
  if (pData->bHasIDAT)
#endif
    MNG_ERROR (pData, MNG_SEQUENCEERROR);
