#ifdef MNG_INCLUDE_JNG
if ((pData->bHasIHDR) || (pData->bHasBASI) || (pData->bHasDHDR) || (pData->bHasJHDR))
#else
  if ((pData->bHasIHDR) || (pData->bHasBASI) || (pData->bHasDHDR))
#endif
  {
    mng_imagep pImage;

#ifndef MNG_NO_DELTA_PNG
    if (pData->bHasDHDR)               /* update delta image ? */
      pImage = (mng_imagep)pData->pObjzero;
    else
#endif
    {
      pImage = (mng_imagep)pData->pCurrentobj;
      if (!pImage)                     /* no object then dump it in obj 0 */
        pImage = (mng_imagep)pData->pObjzero;
    }
                                       /* store for color-processing routines */
    pImage->pImgbuf->iGamma   = ((mng_gamap)pChunk)->iGamma;
    pImage->pImgbuf->bHasGAMA = MNG_TRUE;
  }
  else
  {                                    /* store as global */
    if (!((mng_gamap)pChunk)->bEmpty)
      pData->iGlobalGamma = ((mng_gamap)pChunk)->iGamma;
                                       /* create an animation object */
    return mng_create_ani_gama (pData, pChunk);
  }
