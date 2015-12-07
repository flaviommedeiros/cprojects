#ifdef MNG_INCLUDE_JNG
if ((pData->bHasIHDR) || (pData->bHasBASI) || (pData->bHasDHDR) || (pData->bHasJHDR))
#else
    if ((pData->bHasIHDR) || (pData->bHasBASI) || (pData->bHasDHDR))
#endif
    {
      mng_imagep     pImage;
      mng_imagedatap pBuf;

#ifndef MNG_NO_DELTA_PNG
      if (pData->bHasDHDR)             /* update delta image ? */
        pImage = (mng_imagep)pData->pObjzero;
      else
#endif
      {
        pImage = (mng_imagep)pData->pCurrentobj;
        if (!pImage)                   /* no object then dump it in obj 0 */
          pImage = (mng_imagep)pData->pObjzero;
      
