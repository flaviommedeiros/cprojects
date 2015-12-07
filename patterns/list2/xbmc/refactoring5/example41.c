#ifndef MNG_NO_DELTA_PNG
if (pData->bHasDHDR)               /* delta-image ? */
    {
      if (pData->iDeltatype == MNG_DELTATYPE_REPLACE)
      {
        iRetcode = mng_reset_object_details (pData, (mng_imagep)pData->pDeltaImage,
                                             pData->iDatawidth, pData->iDataheight,
                                             pData->iJHDRimgbitdepth, pData->iJHDRcolortype,
                                             pData->iJHDRalphacompression, pData->iJHDRalphafilter,
                                             pData->iJHDRalphainterlace, MNG_TRUE);

        ((mng_imagep)pData->pDeltaImage)->pImgbuf->iAlphabitdepth    = pData->iJHDRalphabitdepth;
        ((mng_imagep)pData->pDeltaImage)->pImgbuf->iJHDRcompression  = pData->iJHDRimgcompression;
        ((mng_imagep)pData->pDeltaImage)->pImgbuf->iJHDRinterlace    = pData->iJHDRimginterlace;
        ((mng_imagep)pData->pDeltaImage)->pImgbuf->iAlphasampledepth = pData->iJHDRalphabitdepth;
      }
      else
      if ((pData->iDeltatype == MNG_DELTATYPE_BLOCKPIXELADD    ) ||
          (pData->iDeltatype == MNG_DELTATYPE_BLOCKPIXELREPLACE)    )
      {
        ((mng_imagep)pData->pDeltaImage)->pImgbuf->iPixelsampledepth = pData->iJHDRimgbitdepth;
        ((mng_imagep)pData->pDeltaImage)->pImgbuf->iAlphasampledepth = pData->iJHDRalphabitdepth;
      }
      else
      if ((pData->iDeltatype == MNG_DELTATYPE_BLOCKALPHAADD    ) ||
          (pData->iDeltatype == MNG_DELTATYPE_BLOCKALPHAREPLACE)    )
        ((mng_imagep)pData->pDeltaImage)->pImgbuf->iAlphasampledepth = pData->iJHDRalphabitdepth;
      else
      if ((pData->iDeltatype == MNG_DELTATYPE_BLOCKCOLORADD    ) ||
          (pData->iDeltatype == MNG_DELTATYPE_BLOCKCOLORREPLACE)    )
        ((mng_imagep)pData->pDeltaImage)->pImgbuf->iPixelsampledepth = pData->iJHDRimgbitdepth;
        
    }
    else
#endif /* MNG_NO_DELTA_PNG */
    {
      if (pImage)                      /* update object buffer ? */
      {
        iRetcode = mng_reset_object_details (pData, pImage,
                                             pData->iDatawidth, pData->iDataheight,
                                             pData->iJHDRimgbitdepth, pData->iJHDRcolortype,
                                             pData->iJHDRalphacompression, pData->iJHDRalphafilter,
                                             pData->iJHDRalphainterlace, MNG_TRUE);

        pImage->pImgbuf->iAlphabitdepth    = pData->iJHDRalphabitdepth;
        pImage->pImgbuf->iJHDRcompression  = pData->iJHDRimgcompression;
        pImage->pImgbuf->iJHDRinterlace    = pData->iJHDRimginterlace;
        pImage->pImgbuf->iAlphasampledepth = pData->iJHDRalphabitdepth;
      }
      else                             /* update object 0 */
      {
        iRetcode = mng_reset_object_details (pData, (mng_imagep)pData->pObjzero,
                                             pData->iDatawidth, pData->iDataheight,
                                             pData->iJHDRimgbitdepth, pData->iJHDRcolortype,
                                             pData->iJHDRalphacompression, pData->iJHDRalphafilter,
                                             pData->iJHDRalphainterlace, MNG_TRUE);

        ((mng_imagep)pData->pObjzero)->pImgbuf->iAlphabitdepth    = pData->iJHDRalphabitdepth;
        ((mng_imagep)pData->pObjzero)->pImgbuf->iJHDRcompression  = pData->iJHDRimgcompression;
        ((mng_imagep)pData->pObjzero)->pImgbuf->iJHDRinterlace    = pData->iJHDRimginterlace;
        ((mng_imagep)pData->pObjzero)->pImgbuf->iAlphasampledepth = pData->iJHDRalphabitdepth;
      }
    }
