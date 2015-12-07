#ifdef MNG_INCLUDE_JNG
if ((pData->bHasIHDR) || (pData->bHasBASI) || (pData->bHasDHDR) || (pData->bHasJHDR))
#else
  if ((pData->bHasIHDR) || (pData->bHasBASI) || (pData->bHasDHDR))
#endif
    pData->bHasBKGD = MNG_TRUE;        /* indicate bKGD available */
  else
    pData->bHasglobalBKGD = (mng_bool)(iRawlen != 0);
