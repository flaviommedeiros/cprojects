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
