#ifndef MNG_NO_16BIT_SUPPORT
if (pData->bIsRGBA16)            /* 16-bit intermediates ? */
        hTrans = cmsCreateTransform (hProf,         TYPE_RGBA_16_SE,
                                     pData->hProf2, TYPE_RGBA_16_SE,
                                     INTENT_PERCEPTUAL, MNG_CMS_FLAGS);
      else
#endif
        hTrans = cmsCreateTransform (hProf,         TYPE_RGBA_8,
                                     pData->hProf2, TYPE_RGBA_8,
                                     INTENT_PERCEPTUAL, MNG_CMS_FLAGS);
