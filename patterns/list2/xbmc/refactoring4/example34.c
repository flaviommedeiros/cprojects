#ifdef MNG_SUPPORT_DISPLAY
if ((pData->bHasIHDR) || (pData->bHasBASI) || (pData->bHasDHDR) || (pData->bHasJHDR))
#else
  if ((pData->bHasIHDR) || (pData->bHasBASI) || (pData->bHasDHDR))
#endif
  {
    mng_imagep pImage;

#ifndef MNG_NO_DELTA_PNG
    if (pData->bHasDHDR)               /* update delta image ? */
    {                                  /* store in object 0 ! */
      pImage = (mng_imagep)pData->pObjzero;
                                       /* store for color-processing routines */
      pImage->pImgbuf->iRenderingintent = *pRawdata;
      pImage->pImgbuf->bHasSRGB         = MNG_TRUE;
    }
    else
#endif
    {
      pImage = (mng_imagep)pData->pCurrentobj;

      if (!pImage)                     /* no object then dump it in obj 0 */
        pImage = (mng_imagep)pData->pObjzero;
                                       /* store for color-processing routines */
      pImage->pImgbuf->iRenderingintent = *pRawdata;
      pImage->pImgbuf->bHasSRGB         = MNG_TRUE;
    }
  }
  else
  {                                    /* store as global */
    if (iRawlen != 0)
      pData->iGlobalRendintent = *pRawdata;

    {                                  /* create an animation object */
      mng_retcode iRetcode = mng_create_ani_srgb (pData, (mng_bool)(iRawlen == 0),
                                                  pData->iGlobalRendintent);

      if (iRetcode)                    /* on error bail out */
        return iRetcode;
    }
  }
