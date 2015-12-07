#ifdef MNG_INCLUDE_JNG
if ((pData->bHasIHDR) || (pData->bHasBASI) || (pData->bHasDHDR) || (pData->bHasJHDR))
#else
    if ((pData->bHasIHDR) || (pData->bHasBASI) || (pData->bHasDHDR))
#endif
      pData->bHasICCP = MNG_TRUE;      /* indicate we've got it */
    else
      pData->bHasglobalICCP = (mng_bool)(iRawlen != 0);
