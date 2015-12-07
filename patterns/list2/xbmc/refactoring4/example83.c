#ifdef MNG_SUPPORT_DISPLAY
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
    pImage->pImgbuf->iRenderingintent = ((mng_srgbp)pChunk)->iRenderingintent;
    pImage->pImgbuf->bHasSRGB         = MNG_TRUE;
  }
  else
  {                                    /* store as global */
    if (!((mng_srgbp)pChunk)->bEmpty)
      pData->iGlobalRendintent = ((mng_srgbp)pChunk)->iRenderingintent;
                                       /* create an animation object */
    return mng_create_ani_srgb (pData, pChunk);
  }
