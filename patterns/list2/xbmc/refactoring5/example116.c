#ifndef MNG_NO_DELTA_PNG
if (pData->bHasDHDR)                 /* processing delta-image ? */
  {
    mng_imagep pDelta = (mng_imagep)pData->pDeltaImage;

    if (!pData->iBreakpoint)           /* only execute if not broken before */
    {                                  /* make sure to process pixels as well */
      pData->bDeltaimmediate = MNG_FALSE;
                                       /* execute the delta process */
      iRetcode = mng_execute_delta_image (pData, pDelta, (mng_imagep)pObject);

      if (iRetcode)                    /* on error bail out */
        return iRetcode;
    }
                                       /* now go and shoot it off (if required) */
    if ((pDelta->bVisible) && (pDelta->bViewable))
      iRetcode = mng_display_image (pData, pDelta, MNG_FALSE);

    if (!pData->bTimerset)
      pData->bHasDHDR = MNG_FALSE;     /* this image signifies IEND !! */

  }
  else
#endif
  if (pData->pCurrentobj)              /* active object ? */
  {
    mng_imagep     pCurrent = (mng_imagep)pData->pCurrentobj;
    mng_imagedatap pBuf     = pCurrent->pImgbuf;

    if (!pData->iBreakpoint)           /* don't copy it again ! */
    {
      if (pBuf->iImgdatasize)          /* buffer present in active object ? */
                                       /* then drop it */
        MNG_FREE (pData, pBuf->pImgdata, pBuf->iImgdatasize);

#ifndef MNG_SKIPCHUNK_iCCP
      if (pBuf->iProfilesize)          /* iCCP profile present ? */
                                       /* then drop it */
        MNG_FREE (pData, pBuf->pProfile, pBuf->iProfilesize);
#endif
                                       /* now blatently copy the animation buffer */
      MNG_COPY (pBuf, pImage->pImgbuf, sizeof (mng_imagedata));
                                       /* copy viewability */
      pCurrent->bViewable = pImage->bViewable;

      if (pBuf->iImgdatasize)          /* sample buffer present ? */
      {                                /* then make a copy */
        MNG_ALLOC (pData, pBuf->pImgdata, pBuf->iImgdatasize);
        MNG_COPY (pBuf->pImgdata, pImage->pImgbuf->pImgdata, pBuf->iImgdatasize);
      }

#ifndef MNG_SKIPCHUNK_iCCP
      if (pBuf->iProfilesize)          /* iCCP profile present ? */
      {                                /* then make a copy */
        MNG_ALLOC (pData, pBuf->pProfile, pBuf->iProfilesize);
        MNG_COPY (pBuf->pProfile, pImage->pImgbuf->pProfile, pBuf->iProfilesize);
      }
#endif
    }
                                       /* now go and shoot it off (if required) */
    if ((pCurrent->bVisible) && (pCurrent->bViewable))
      iRetcode = mng_display_image (pData, pCurrent, MNG_FALSE);
  }
  else
  {
    mng_imagep     pObjzero = (mng_imagep)pData->pObjzero;
    mng_imagedatap pBuf     = pObjzero->pImgbuf;

    if (!pData->iBreakpoint)           /* don't copy it again ! */
    {
      if (pBuf->iImgdatasize)          /* buffer present in active object ? */
                                       /* then drop it */
        MNG_FREE (pData, pBuf->pImgdata, pBuf->iImgdatasize);

#ifndef MNG_SKIPCHUNK_iCCP
      if (pBuf->iProfilesize)          /* iCCP profile present ? */
                                       /* then drop it */
        MNG_FREE (pData, pBuf->pProfile, pBuf->iProfilesize);
#endif
                                       /* now blatently copy the animation buffer */
      MNG_COPY (pBuf, pImage->pImgbuf, sizeof (mng_imagedata));
                                       /* copy viewability */
      pObjzero->bViewable = pImage->bViewable;

      if (pBuf->iImgdatasize)          /* sample buffer present ? */
      {                                /* then make a copy */
        MNG_ALLOC (pData, pBuf->pImgdata, pBuf->iImgdatasize);
        MNG_COPY (pBuf->pImgdata, pImage->pImgbuf->pImgdata, pBuf->iImgdatasize);
      }

#ifndef MNG_SKIPCHUNK_iCCP
      if (pBuf->iProfilesize)          /* iCCP profile present ? */
      {                                /* then make a copy */
        MNG_ALLOC (pData, pBuf->pProfile, pBuf->iProfilesize);
        MNG_COPY (pBuf->pProfile, pImage->pImgbuf->pProfile, pBuf->iProfilesize);
      }
#endif
    }
                                       /* now go and show it */
    iRetcode = mng_display_image (pData, pObjzero, MNG_FALSE);
  }
