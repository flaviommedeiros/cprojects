#ifdef MNG_SUPPORT_DISPLAY
if ((pData->bHasIHDR) || (pData->bHasBASI) || (pData->bHasDHDR) || (pData->bHasJHDR))
#else
    if ((pData->bHasIHDR) || (pData->bHasBASI) || (pData->bHasDHDR))
#endif
    {
      mng_imagep pImage;

#ifndef MNG_NO_DELTA_PNG
      if (pData->bHasDHDR)             /* update delta image ? */
      {                                /* store in object 0 ! */
        pImage = (mng_imagep)pData->pObjzero;

        if (pImage->pImgbuf->pProfile) /* profile existed ? */
          MNG_FREEX (pData, pImage->pImgbuf->pProfile, pImage->pImgbuf->iProfilesize);
                                       /* allocate a buffer & copy it */
        MNG_ALLOC (pData, pImage->pImgbuf->pProfile, ((mng_iccpp)pChunk)->iProfilesize);
        MNG_COPY  (pImage->pImgbuf->pProfile, ((mng_iccpp)pChunk)->pProfile, ((mng_iccpp)pChunk)->iProfilesize);
                                       /* store its length as well */
        pImage->pImgbuf->iProfilesize = ((mng_iccpp)pChunk)->iProfilesize;
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
        MNG_ALLOC (pData, pImage->pImgbuf->pProfile, ((mng_iccpp)pChunk)->iProfilesize);
        MNG_COPY  (pImage->pImgbuf->pProfile, ((mng_iccpp)pChunk)->pProfile, ((mng_iccpp)pChunk)->iProfilesize);
                                       /* store its length as well */
        pImage->pImgbuf->iProfilesize = ((mng_iccpp)pChunk)->iProfilesize;
        pImage->pImgbuf->bHasICCP     = MNG_TRUE;
      }
    }
    else
    {                                  /* store as global */
      if (pData->pGlobalProfile)     /* did we have a global profile ? */
        MNG_FREEX (pData, pData->pGlobalProfile, pData->iGlobalProfilesize);

      if (((mng_iccpp)pChunk)->bEmpty) /* empty chunk ? */
      {
        pData->iGlobalProfilesize = 0; /* reset to null */
        pData->pGlobalProfile     = MNG_NULL;
      }
      else
      {                                /* allocate a global buffer & copy it */
        MNG_ALLOC (pData, pData->pGlobalProfile, ((mng_iccpp)pChunk)->iProfilesize);
        MNG_COPY  (pData->pGlobalProfile, ((mng_iccpp)pChunk)->pProfile, ((mng_iccpp)pChunk)->iProfilesize);
                                       /* store its length as well */
        pData->iGlobalProfilesize = ((mng_iccpp)pChunk)->iProfilesize;
      }
                                       /* create an animation object */
      return mng_create_ani_iccp (pData, pChunk);
    }
