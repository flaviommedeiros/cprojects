#ifdef MNG_INCLUDE_JNG
if ((pData->bHasIHDR) || (pData->bHasBASI) || (pData->bHasDHDR) || (pData->bHasJHDR))
#else
    if ((pData->bHasIHDR) || (pData->bHasBASI) || (pData->bHasDHDR))
#endif
    {
      if ((iRawlen == 0) && (!(pDescr->iAllowed & MNG_DESCR_EMPTYEMBED)))
        MNG_ERROR (pData, MNG_INVALIDLENGTH);
    } else {
      if ((iRawlen == 0) && (!(pDescr->iAllowed & MNG_DESCR_EMPTYGLOBAL)))
        MNG_ERROR (pData, MNG_INVALIDLENGTH);
    }
