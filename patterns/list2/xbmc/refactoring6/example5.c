if ((pData->bHasBASI) ||             /* was it a BASI stream */
      (bDodisplay)      ||             /* or should we display the JNG */
#ifndef MNG_SKIPCHUNK_MAGN
      (bMagnify)        ||             /* or should we magnify it */
#endif
                                       /* or did we get broken here last time ? */
      ((pData->iBreakpoint) && (pData->iBreakpoint != 8)))
  {
    mng_imagep pImage = (mng_imagep)pData->pCurrentobj;

    if (!pImage)                       /* or was it object 0 ? */
      pImage = (mng_imagep)pData->pObjzero;
                                       /* display it now then ? */
    if ((pImage->bVisible) && (pImage->bViewable))
    {                                  /* ok, so do it */
      iRetcode = mng_display_image (pData, pImage, bDodisplay);

      if (iRetcode)                    /* on error bail out */
        return iRetcode;

      if (pData->bTimerset)            /* timer break ? */
        pData->iBreakpoint = 6;
    }
  }
#ifndef MNG_NO_DELTA_PNG
  else
  if ((pData->bHasDHDR) ||             /* was it a DHDR stream */
      (pData->iBreakpoint == 8))       /* or did we get broken here last time ? */
  {
    mng_imagep pImage = (mng_imagep)pData->pDeltaImage;

    if (!pData->iBreakpoint)
    {                                  /* perform the delta operations needed */
      iRetcode = mng_execute_delta_image (pData, pImage, (mng_imagep)pData->pObjzero);

      if (iRetcode)                    /* on error bail out */
        return iRetcode;
    }
                                       /* display it now then ? */
    if ((pImage->bVisible) && (pImage->bViewable))
    {                                  /* ok, so do it */
      iRetcode = mng_display_image (pData, pImage, MNG_FALSE);

      if (iRetcode)                    /* on error bail out */
        return iRetcode;

      if (pData->bTimerset)            /* timer break ? */
        pData->iBreakpoint = 8;
    }
  }
