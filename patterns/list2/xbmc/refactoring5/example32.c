#ifndef MNG_NO_DELTA_PNG
if (pData->bHasDHDR)               /* is a delta-image ? */
    {
      if (pData->iDeltatype == MNG_DELTATYPE_REPLACE)
        iRetcode = mng_reset_object_details (pData, (mng_imagep)pData->pDeltaImage,
                                             pData->iDatawidth, pData->iDataheight,
                                             pData->iBitdepth, pData->iColortype,
                                             pData->iCompression, pData->iFilter,
                                             pData->iInterlace, MNG_TRUE);
      else
      if ((pData->iDeltatype == MNG_DELTATYPE_BLOCKPIXELADD    ) ||
          (pData->iDeltatype == MNG_DELTATYPE_BLOCKPIXELREPLACE)    )
      {
        ((mng_imagep)pData->pDeltaImage)->pImgbuf->iPixelsampledepth = pData->iBitdepth;
        ((mng_imagep)pData->pDeltaImage)->pImgbuf->iAlphasampledepth = pData->iBitdepth;
      }
      else
      if ((pData->iDeltatype == MNG_DELTATYPE_BLOCKALPHAADD    ) ||
          (pData->iDeltatype == MNG_DELTATYPE_BLOCKALPHAREPLACE)    )
        ((mng_imagep)pData->pDeltaImage)->pImgbuf->iAlphasampledepth = pData->iBitdepth;
      else
      if ((pData->iDeltatype == MNG_DELTATYPE_BLOCKCOLORADD    ) ||
          (pData->iDeltatype == MNG_DELTATYPE_BLOCKCOLORREPLACE)    )
        ((mng_imagep)pData->pDeltaImage)->pImgbuf->iPixelsampledepth = pData->iBitdepth;

      if (!iRetcode)
      {                                /* process immediately if bitdepth & colortype are equal */
        pData->bDeltaimmediate =
          (mng_bool)((pData->iBitdepth  == ((mng_imagep)pData->pDeltaImage)->pImgbuf->iBitdepth ) &&
                     (pData->iColortype == ((mng_imagep)pData->pDeltaImage)->pImgbuf->iColortype)    );
                                       /* be sure to reset object 0 */
        iRetcode = mng_reset_object_details (pData, (mng_imagep)pData->pObjzero,
                                             pData->iDatawidth, pData->iDataheight,
                                             pData->iBitdepth, pData->iColortype,
                                             pData->iCompression, pData->iFilter,
                                             pData->iInterlace, MNG_TRUE);
      }
    }
    else
#endif
    {
      if (pImage)                      /* update object buffer ? */
        iRetcode = mng_reset_object_details (pData, pImage,
                                             pData->iDatawidth, pData->iDataheight,
                                             pData->iBitdepth, pData->iColortype,
                                             pData->iCompression, pData->iFilter,
                                             pData->iInterlace, MNG_TRUE);
      else
        iRetcode = mng_reset_object_details (pData, (mng_imagep)pData->pObjzero,
                                             pData->iDatawidth, pData->iDataheight,
                                             pData->iBitdepth, pData->iColortype,
                                             pData->iCompression, pData->iFilter,
                                             pData->iInterlace, MNG_TRUE);
    }
