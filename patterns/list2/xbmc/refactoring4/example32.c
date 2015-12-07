#ifdef MNG_INCLUDE_JNG
if ((pData->bHasIHDR) || (pData->bHasBASI) || (pData->bHasDHDR) || (pData->bHasJHDR))
#else
  if ((pData->bHasIHDR) || (pData->bHasBASI) || (pData->bHasDHDR))
#endif
  {                                    /* length must be exactly 1 */
    if (iRawlen != 1)
      MNG_ERROR (pData, MNG_INVALIDLENGTH);
  }
  else
  {                                    /* length must be empty or exactly 1 */
    if ((iRawlen != 0) && (iRawlen != 1))
      MNG_ERROR (pData, MNG_INVALIDLENGTH);
  }
