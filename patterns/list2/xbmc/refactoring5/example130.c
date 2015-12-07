#ifndef MNG_NO_DELTA_PNG
if (pData->bHasDHDR)             /* update delta image ? */
      {                                /* store in object 0 ! */
        pImage = (mng_imagep)pData->pObjzero;

        if (pImage->pImgbuf->pProfile) /* profile existed ? */
          MNG_FREEX (pData, pImage->pImgbuf->pProfile, pImage->pImgbuf->iProfilesize);
                                       /* allocate a buffer & copy it */
        MNG_ALLOC (pData, pImage->pImgbuf->pProfile, iProfilesize);
        MNG_COPY  (pImage->pImgbuf->pProfile, pBuf, iProfilesize);
                                       /* store its length as well */
        pImage->pImgbuf->iProfilesize = iProfilesize;
        pImage->pImgbuf->bHasICCP     = MNG_TRUE;
      }
      else
#endif
      {
        pImage = (mng_imagep)pData->pCurrentobj;

        if (!pImage)                   /* no object then dump it in obj 0 */
          pImage = (mng_imagep)pData->pObjzero;

        if (pImage->pImgbuf->pProfile) /* profile existed ? */
          MNG_FREEX (pData, pImage->pImgbuf->pProfile, pImage->pImgbuf->iProfilesize);
                                       /* allocate a buffer & copy it */
        MNG_ALLOC (pData, pImage->pImgbuf->pProfile, iProfilesize);
        MNG_COPY  (pImage->pImgbuf->pProfile, pBuf, iProfilesize);
                                       /* store its length as well */
        pImage->pImgbuf->iProfilesize = iProfilesize;
        pImage->pImgbuf->bHasICCP     = MNG_TRUE;
      }
