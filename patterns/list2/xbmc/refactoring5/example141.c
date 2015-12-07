#ifdef MNG_SUPPORT_DISPLAY
if ((pData->bHasIHDR) || (pData->bHasBASI) || (pData->bHasDHDR))
  {
    mng_imagep     pImage;
    mng_imagedatap pBuf;

#ifndef MNG_NO_DELTA_PNG
    if (pData->bHasDHDR)               /* processing delta-image ? */
    {                                  /* store in object 0 !!! */
      pImage           = (mng_imagep)pData->pObjzero;
      pBuf             = pImage->pImgbuf;
      pBuf->bHasPLTE   = MNG_TRUE;     /* it's definitely got a PLTE now */
      pBuf->iPLTEcount = ((mng_pltep)pChunk)->iEntrycount;
      MNG_COPY (pBuf->aPLTEentries, ((mng_pltep)pChunk)->aEntries,
                sizeof (pBuf->aPLTEentries));
    }
    else
#endif
    {                                  /* get the current object */
      pImage = (mng_imagep)pData->pCurrentobj;
      if (!pImage)                     /* no object then dump it in obj 0 */
        pImage = (mng_imagep)pData->pObjzero;

      pBuf = pImage->pImgbuf;          /* address the object buffer */
      pBuf->bHasPLTE = MNG_TRUE;       /* and tell it it's got a PLTE now */

      if (((mng_pltep)pChunk)->bEmpty) /* if empty, inherit from global */
      {
        pBuf->iPLTEcount = pData->iGlobalPLTEcount;
        MNG_COPY (pBuf->aPLTEentries, pData->aGlobalPLTEentries,
                  sizeof (pBuf->aPLTEentries));

        if (pData->bHasglobalTRNS)     /* also copy global tRNS ? */
        {
          mng_uint32 iRawlen2  = pData->iGlobalTRNSrawlen;
          mng_uint8p pRawdata2 = (mng_uint8p)(pData->aGlobalTRNSrawdata);
                                       /* indicate tRNS available */
          pBuf->bHasTRNS = MNG_TRUE;
                                       /* global length oke ? */
          if ((iRawlen2 == 0) || (iRawlen2 > pBuf->iPLTEcount))
            MNG_ERROR (pData, MNG_GLOBALLENGTHERR);
                                       /* copy it */
          pBuf->iTRNScount = iRawlen2;
          MNG_COPY (pBuf->aTRNSentries, pRawdata2, iRawlen2);
        }
      }
      else
      {                                /* store fields for future reference */
        pBuf->iPLTEcount = ((mng_pltep)pChunk)->iEntrycount;
        MNG_COPY (pBuf->aPLTEentries, ((mng_pltep)pChunk)->aEntries,
                  sizeof (pBuf->aPLTEentries));
      }
    }
  }
  else                                 /* store as global */
  {
    pData->iGlobalPLTEcount = ((mng_pltep)pChunk)->iEntrycount;
    MNG_COPY (pData->aGlobalPLTEentries, ((mng_pltep)pChunk)->aEntries,
              sizeof (pData->aGlobalPLTEentries));
                                       /* create an animation object */
    return mng_create_ani_plte (pData);
  }
