#ifndef MNG_OPTIMIZE_DISPLAYCALLS
while ((iX <= iLastid) && (!pData->bTimerset))
#else
  while ((iX <= pData->iMAGNlastid) && (!pData->bTimerset))
#endif
  {
    pData->iMAGNcurrentid = iX;

    if (iX)                            /* only real objects ! */
    {
      pImage = mng_find_imageobject (pData, iX);
                                       /* object exists & is not frozen  &
                                          is visible & is viewable ? */
      if ((pImage) && (!pImage->bFrozen) &&
          (pImage->bVisible) && (pImage->bViewable))
      {
        mng_retcode iRetcode = mng_display_image (pData, pImage, MNG_FALSE);
        if (iRetcode)
          return iRetcode;
      }
    }

    iX++;
  }
