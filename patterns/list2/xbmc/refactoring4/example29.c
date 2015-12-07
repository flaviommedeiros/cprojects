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
      {                                /* store it in object 0 ! */
        pImage = (mng_imagep)pData->pObjzero;

        pBuf = pImage->pImgbuf;        /* address object buffer */
        pBuf->bHasCHRM = MNG_TRUE;     /* and tell it it's got a CHRM now */
                                       /* store for color-processing routines */
        pBuf->iWhitepointx   = iWhitepointx;
        pBuf->iWhitepointy   = iWhitepointy;
        pBuf->iPrimaryredx   = iPrimaryredx;
        pBuf->iPrimaryredy   = iPrimaryredy;
        pBuf->iPrimarygreenx = iPrimarygreenx;
        pBuf->iPrimarygreeny = iPrimarygreeny;
        pBuf->iPrimarybluex  = iPrimarybluex;
        pBuf->iPrimarybluey  = iPrimarybluey;
      }
      else
#endif
      {
        pImage = (mng_imagep)pData->pCurrentobj;

        if (!pImage)                   /* no object then dump it in obj 0 */
          pImage = (mng_imagep)pData->pObjzero;

        pBuf = pImage->pImgbuf;        /* address object buffer */
        pBuf->bHasCHRM = MNG_TRUE;     /* and tell it it's got a CHRM now */
                                       /* store for color-processing routines */
        pBuf->iWhitepointx   = iWhitepointx;
        pBuf->iWhitepointy   = iWhitepointy;
        pBuf->iPrimaryredx   = iPrimaryredx;
        pBuf->iPrimaryredy   = iPrimaryredy;
        pBuf->iPrimarygreenx = iPrimarygreenx;
        pBuf->iPrimarygreeny = iPrimarygreeny;
        pBuf->iPrimarybluex  = iPrimarybluex;
        pBuf->iPrimarybluey  = iPrimarybluey;
      }
    }
    else
    {                                  /* store as global */
      if (iRawlen != 0)
      {
        pData->iGlobalWhitepointx   = iWhitepointx;
        pData->iGlobalWhitepointy   = iWhitepointy;
        pData->iGlobalPrimaryredx   = iPrimaryredx;
        pData->iGlobalPrimaryredy   = iPrimaryredy;
        pData->iGlobalPrimarygreenx = iPrimarygreenx;
        pData->iGlobalPrimarygreeny = iPrimarygreeny;
        pData->iGlobalPrimarybluex  = iPrimarybluex;
        pData->iGlobalPrimarybluey  = iPrimarybluey;
      }

      {                                /* create an animation object */
        mng_retcode iRetcode = mng_create_ani_chrm (pData, (mng_bool)(iRawlen == 0),
                                                    iWhitepointx,   iWhitepointy,
                                                    iPrimaryredx,   iPrimaryredy,
                                                    iPrimarygreenx, iPrimarygreeny,
                                                    iPrimarybluex,  iPrimarybluey);

        if (iRetcode)                  /* on error bail out */
          return iRetcode;
      }
    }
