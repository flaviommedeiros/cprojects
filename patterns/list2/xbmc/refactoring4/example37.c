#ifdef MNG_INCLUDE_JNG
if ((pData->bHasIHDR) || (pData->bHasBASI) || (pData->bHasDHDR) || (pData->bHasJHDR))
#else
  if ((pData->bHasIHDR) || (pData->bHasBASI) || (pData->bHasDHDR))
#endif
  {                                    /* length must be at least 2 */
    if (iRawlen < 2)
      MNG_ERROR (pData, MNG_INVALIDLENGTH);
  }
  else
  {                                    /* length must be empty or at least 2 */
    if ((iRawlen != 0) && (iRawlen < 2))
      MNG_ERROR (pData, MNG_INVALIDLENGTH);
  }
