#ifndef MNG_OPTIMIZE_DISPLAYCALLS
if (iDeltatype == MNG_DELTATYPE_REPLACE)
#else
      if (pData->iDHDRdeltatype == MNG_DELTATYPE_REPLACE)
#endif
      {
        iRetcode = mng_reset_object_details (pData, pImage,
                                             pData->iDatawidth, pData->iDataheight,
                                             pData->iBitdepth, pData->iColortype,
                                             pData->iCompression, pData->iFilter,
                                             pData->iInterlace, MNG_FALSE);

        if (iRetcode)                  /* on error bail out */
          return iRetcode;

        pData->pStoreobj = pImage;     /* and store straight into this object */
      }
      else
      {
        mng_imagedatap pBufzero, pBuf;
                                       /* we store in object 0 and process it later */
        pData->pStoreobj = pData->pObjzero;
                                       /* make sure to initialize object 0 then */
        iRetcode = mng_reset_object_details (pData, (mng_imagep)pData->pObjzero,
                                             pData->iDatawidth, pData->iDataheight,
                                             pData->iBitdepth, pData->iColortype,
                                             pData->iCompression, pData->iFilter,
                                             pData->iInterlace, MNG_TRUE);

        if (iRetcode)                  /* on error bail out */
          return iRetcode;

        pBuf     = pImage->pImgbuf;    /* copy possible palette & cheap transparency */
        pBufzero = ((mng_imagep)pData->pObjzero)->pImgbuf;

        pBufzero->bHasPLTE = pBuf->bHasPLTE;
        pBufzero->bHasTRNS = pBuf->bHasTRNS;

        if (pBufzero->bHasPLTE)        /* copy palette ? */
        {
          mng_uint32 iX;

          pBufzero->iPLTEcount = pBuf->iPLTEcount;

          for (iX = 0; iX < pBuf->iPLTEcount; iX++)
          {
            pBufzero->aPLTEentries [iX].iRed   = pBuf->aPLTEentries [iX].iRed;
            pBufzero->aPLTEentries [iX].iGreen = pBuf->aPLTEentries [iX].iGreen;
            pBufzero->aPLTEentries [iX].iBlue  = pBuf->aPLTEentries [iX].iBlue;
          }
        }

        if (pBufzero->bHasTRNS)        /* copy cheap transparency ? */
        {
          pBufzero->iTRNSgray  = pBuf->iTRNSgray;
          pBufzero->iTRNSred   = pBuf->iTRNSred;
          pBufzero->iTRNSgreen = pBuf->iTRNSgreen;
          pBufzero->iTRNSblue  = pBuf->iTRNSblue;
          pBufzero->iTRNScount = pBuf->iTRNScount;

          MNG_COPY (pBufzero->aTRNSentries, pBuf->aTRNSentries,
                    sizeof (pBufzero->aTRNSentries));
        }
                                       /* process immediately if bitdepth & colortype are equal */
        pData->bDeltaimmediate =
          (mng_bool)((pData->bDisplaying) && (!pData->bSkipping) &&
                     ((pData->bRunning) || (pData->bSearching)) &&
                     (pData->iBitdepth  == ((mng_imagep)pData->pDeltaImage)->pImgbuf->iBitdepth ) &&
                     (pData->iColortype == ((mng_imagep)pData->pDeltaImage)->pImgbuf->iColortype)    );
      }
