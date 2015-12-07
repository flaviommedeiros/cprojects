#ifndef MNG_SKIPCHUNK_iCCP
if (((pBuf) && (pBuf->bHasICCP)) || ((bGlobal) && (pData->bHasglobalICCP)))
    {
      if (!pData->hProf2)              /* output profile not defined ? */
      {                                /* then assume sRGB !! */
        pData->hProf2 = mnglcms_createsrgbprofile ();

        if (!pData->hProf2)            /* handle error ? */
          MNG_ERRORL (pData, MNG_LCMS_NOHANDLE);
      }

      if ((pBuf) && (pBuf->bHasICCP))  /* generate a profile handle */
        hProf = cmsOpenProfileFromMem (pBuf->pProfile, pBuf->iProfilesize);
      else
        hProf = cmsOpenProfileFromMem (pData->pGlobalProfile, pData->iGlobalProfilesize);

      pData->hProf1 = hProf;           /* save for future use */

      if (!hProf)                      /* handle error ? */
        MNG_ERRORL (pData, MNG_LCMS_NOHANDLE);

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

      pData->hTrans = hTrans;          /* save for future use */

      if (!hTrans)                     /* handle error ? */
        MNG_ERRORL (pData, MNG_LCMS_NOTRANS);
                                       /* load color-correction routine */
      pData->fCorrectrow = (mng_fptr)mng_correct_full_cms;

      return MNG_NOERROR;              /* and done */
    }
    else
#endif
    if (((pBuf) && (pBuf->bHasSRGB)) || ((bGlobal) && (pData->bHasglobalSRGB)))
    {
      mng_uint8 iIntent;

      if (pData->bIssRGB)              /* sRGB system ? */
        return MNG_NOERROR;            /* no conversion required */

      if (!pData->hProf3)              /* sRGB profile not defined ? */
      {                                /* then create it implicitly !! */
        pData->hProf3 = mnglcms_createsrgbprofile ();

        if (!pData->hProf3)            /* handle error ? */
          MNG_ERRORL (pData, MNG_LCMS_NOHANDLE);
      }

      hProf = pData->hProf3;           /* convert from sRGB profile */

      if ((pBuf) && (pBuf->bHasSRGB))  /* determine rendering intent */
        iIntent = pBuf->iRenderingintent;
      else
        iIntent = pData->iGlobalRendintent;

      if (pData->bIsRGBA16)            /* 16-bit intermediates ? */
        hTrans = cmsCreateTransform (hProf,         TYPE_RGBA_16_SE,
                                     pData->hProf2, TYPE_RGBA_16_SE,
                                     iIntent, MNG_CMS_FLAGS);
      else
        hTrans = cmsCreateTransform (hProf,         TYPE_RGBA_8,
                                     pData->hProf2, TYPE_RGBA_8,
                                     iIntent, MNG_CMS_FLAGS);

      pData->hTrans = hTrans;          /* save for future use */

      if (!hTrans)                     /* handle error ? */
        MNG_ERRORL (pData, MNG_LCMS_NOTRANS);
                                       /* load color-correction routine */
      pData->fCorrectrow = (mng_fptr)mng_correct_full_cms;

      return MNG_NOERROR;              /* and done */
    }
    else
    if ( (((pBuf) && (pBuf->bHasCHRM)) || ((bGlobal) && (pData->bHasglobalCHRM))) &&
         ( ((pBuf) && (pBuf->bHasGAMA) && (pBuf->iGamma > 0)) ||
           ((bGlobal) && (pData->bHasglobalGAMA) && (pData->iGlobalGamma > 0))  )    )
    {
      mng_CIExyY       sWhitepoint;
      mng_CIExyYTRIPLE sPrimaries;
      mng_gammatabp    pGammatable[3];
      mng_float        dGamma;

      if (!pData->hProf2)              /* output profile not defined ? */
      {                                /* then assume sRGB !! */
        pData->hProf2 = mnglcms_createsrgbprofile ();

        if (!pData->hProf2)            /* handle error ? */
          MNG_ERRORL (pData, MNG_LCMS_NOHANDLE);
      }

#ifndef MNG_SKIPCHUNK_cHRM
      if ((pBuf) && (pBuf->bHasCHRM))  /* local cHRM ? */
      {
        sWhitepoint.x      = (mng_float)pBuf->iWhitepointx   / 100000;
        sWhitepoint.y      = (mng_float)pBuf->iWhitepointy   / 100000;
        sPrimaries.Red.x   = (mng_float)pBuf->iPrimaryredx   / 100000;
        sPrimaries.Red.y   = (mng_float)pBuf->iPrimaryredy   / 100000;
        sPrimaries.Green.x = (mng_float)pBuf->iPrimarygreenx / 100000;
        sPrimaries.Green.y = (mng_float)pBuf->iPrimarygreeny / 100000;
        sPrimaries.Blue.x  = (mng_float)pBuf->iPrimarybluex  / 100000;
        sPrimaries.Blue.y  = (mng_float)pBuf->iPrimarybluey  / 100000;
      }
      else
      {
        sWhitepoint.x      = (mng_float)pData->iGlobalWhitepointx   / 100000;
        sWhitepoint.y      = (mng_float)pData->iGlobalWhitepointy   / 100000;
        sPrimaries.Red.x   = (mng_float)pData->iGlobalPrimaryredx   / 100000;
        sPrimaries.Red.y   = (mng_float)pData->iGlobalPrimaryredy   / 100000;
        sPrimaries.Green.x = (mng_float)pData->iGlobalPrimarygreenx / 100000;
        sPrimaries.Green.y = (mng_float)pData->iGlobalPrimarygreeny / 100000;
        sPrimaries.Blue.x  = (mng_float)pData->iGlobalPrimarybluex  / 100000;
        sPrimaries.Blue.y  = (mng_float)pData->iGlobalPrimarybluey  / 100000;
      }
#endif

      sWhitepoint.Y      =             /* Y component is always 1.0 */
      sPrimaries.Red.Y   =
      sPrimaries.Green.Y =
      sPrimaries.Blue.Y  = 1.0;

      if ((pBuf) && (pBuf->bHasGAMA))  /* get the gamma value */
        dGamma = (mng_float)pBuf->iGamma / 100000;
      else
        dGamma = (mng_float)pData->iGlobalGamma / 100000;

      dGamma = pData->dViewgamma / dGamma;

      pGammatable [0] =                /* and build the lookup tables */
      pGammatable [1] =
      pGammatable [2] = cmsBuildGamma (256, dGamma);

      if (!pGammatable [0])            /* enough memory ? */
        MNG_ERRORL (pData, MNG_LCMS_NOMEM);
                                       /* create the profile */
      hProf = cmsCreateRGBProfile (&sWhitepoint, &sPrimaries, pGammatable);

      cmsFreeGamma (pGammatable [0]);  /* free the temporary gamma tables ? */
                                       /* yes! but just the one! */

      pData->hProf1 = hProf;           /* save for future use */

      if (!hProf)                      /* handle error ? */
        MNG_ERRORL (pData, MNG_LCMS_NOHANDLE);

      if (pData->bIsRGBA16)            /* 16-bit intermediates ? */
        hTrans = cmsCreateTransform (hProf,         TYPE_RGBA_16_SE,
                                     pData->hProf2, TYPE_RGBA_16_SE,
                                     INTENT_PERCEPTUAL, MNG_CMS_FLAGS);
      else
        hTrans = cmsCreateTransform (hProf,         TYPE_RGBA_8,
                                     pData->hProf2, TYPE_RGBA_8,
                                     INTENT_PERCEPTUAL, MNG_CMS_FLAGS);

      pData->hTrans = hTrans;          /* save for future use */

      if (!hTrans)                     /* handle error ? */
        MNG_ERRORL (pData, MNG_LCMS_NOTRANS);
                                       /* load color-correction routine */
      pData->fCorrectrow = (mng_fptr)mng_correct_full_cms;

      return MNG_NOERROR;              /* and done */
    }
