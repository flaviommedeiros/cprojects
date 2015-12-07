#ifndef MNG_NO_DELTA_PNG
if (pData->bHasDHDR)               /* update delta image ? */
    {                                  /* store in object 0 ! */
      pImage = (mng_imagep)pData->pObjzero;
                                       /* store for color-processing routines */
      pImage->pImgbuf->iGamma   = mng_get_uint32 (pRawdata);
      pImage->pImgbuf->bHasGAMA = MNG_TRUE;
    }
    else
#endif
    {
      pImage = (mng_imagep)pData->pCurrentobj;

      if (!pImage)                     /* no object then dump it in obj 0 */
        pImage = (mng_imagep)pData->pObjzero;
                                       /* store for color-processing routines */
      pImage->pImgbuf->iGamma   = mng_get_uint32 (pRawdata);
      pImage->pImgbuf->bHasGAMA = MNG_TRUE;
    }
