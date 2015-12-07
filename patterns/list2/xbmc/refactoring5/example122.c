#ifndef MNG_NO_DELTA_PNG
if (pData->bHasDHDR)               /* processing delta-image ? */
    {                                  /* store in object 0 !!! */
      pImage           = (mng_imagep)pData->pObjzero;
      pBuf             = pImage->pImgbuf;
      pBuf->bHasPLTE   = MNG_TRUE;     /* it's definitely got a PLTE now */
      pBuf->iPLTEcount = iRawlen / 3;  /* this is the exact length */
      pRawdata2        = pRawdata;     /* copy the entries */

      for (iX = 0; iX < iRawlen / 3; iX++)
      {
        pBuf->aPLTEentries[iX].iRed   = *pRawdata2;
        pBuf->aPLTEentries[iX].iGreen = *(pRawdata2+1);
        pBuf->aPLTEentries[iX].iBlue  = *(pRawdata2+2);

        pRawdata2 += 3;
      }
    }
    else
#endif
    {                                  /* get the current object */
      pImage = (mng_imagep)pData->pCurrentobj;

      if (!pImage)                     /* no object then dump it in obj 0 */
        pImage = (mng_imagep)pData->pObjzero;

      pBuf = pImage->pImgbuf;          /* address the object buffer */
      pBuf->bHasPLTE = MNG_TRUE;       /* and tell it it's got a PLTE now */

      if (!iRawlen)                    /* if empty, inherit from global */
      {
        pBuf->iPLTEcount = pData->iGlobalPLTEcount;
        MNG_COPY (pBuf->aPLTEentries, pData->aGlobalPLTEentries,
                  sizeof (pBuf->aPLTEentries));

        if (pData->bHasglobalTRNS)     /* also copy global tRNS ? */
        {                              /* indicate tRNS available */
          pBuf->bHasTRNS = MNG_TRUE;

          iRawlen2  = pData->iGlobalTRNSrawlen;
          pRawdata2 = (mng_uint8p)(pData->aGlobalTRNSrawdata);
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
        pBuf->iPLTEcount = iRawlen / 3;
        pRawdata2        = pRawdata;

        for (iX = 0; iX < pBuf->iPLTEcount; iX++)
        {
          pBuf->aPLTEentries[iX].iRed   = *pRawdata2;
          pBuf->aPLTEentries[iX].iGreen = *(pRawdata2+1);
          pBuf->aPLTEentries[iX].iBlue  = *(pRawdata2+2);

          pRawdata2 += 3;
        }
      }
    }
