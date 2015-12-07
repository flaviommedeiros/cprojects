#ifdef MNG_INCLUDE_JNG
if (pData->bHasJHDR)
  {
    pBuf->bHasBKGD = MNG_TRUE;         /* tell the object it's got bKGD now */

    switch (pData->iJHDRcolortype)     /* store fields for future reference */
    {
      case  8 : ;                      /* gray */
      case 12 : {                      /* graya */
                  pBuf->iBKGDgray  = mng_get_uint16 (pRawdata);
                  break;
                }
      case 10 : ;                      /* rgb */
      case 14 : {                      /* rgba */
                  pBuf->iBKGDred   = mng_get_uint16 (pRawdata);
                  pBuf->iBKGDgreen = mng_get_uint16 (pRawdata+2);
                  pBuf->iBKGDblue  = mng_get_uint16 (pRawdata+4);
                  break;
                }
    }
  }
  else
#endif /* MNG_INCLUDE_JNG */
  if ((pData->bHasIHDR) || (pData->bHasBASI) || (pData->bHasDHDR))
  {
    pBuf->bHasBKGD = MNG_TRUE;         /* tell the object it's got bKGD now */

    switch (pData->iColortype)         /* store fields for future reference */
    {
      case 0 : ;                        /* gray */
      case 4 : {                        /* graya */
                 pBuf->iBKGDgray  = mng_get_uint16 (pRawdata);
                 break;
               }
      case 2 : ;                        /* rgb */
      case 6 : {                        /* rgba */
                 pBuf->iBKGDred   = mng_get_uint16 (pRawdata);
                 pBuf->iBKGDgreen = mng_get_uint16 (pRawdata+2);
                 pBuf->iBKGDblue  = mng_get_uint16 (pRawdata+4);
                 break;
               }
      case 3 : {                        /* indexed */
                 pBuf->iBKGDindex = *pRawdata;
                 break;
               }
    }
  }
  else                                 /* store as global */
  {
    if (iRawlen)
    {
      pData->iGlobalBKGDred   = mng_get_uint16 (pRawdata);
      pData->iGlobalBKGDgreen = mng_get_uint16 (pRawdata+2);
      pData->iGlobalBKGDblue  = mng_get_uint16 (pRawdata+4);
    }

    {                                  /* create an animation object */
      mng_retcode iRetcode = mng_create_ani_bkgd (pData, pData->iGlobalBKGDred,
                                                  pData->iGlobalBKGDgreen,
                                                  pData->iGlobalBKGDblue);

      if (iRetcode)                    /* on error bail out */
        return iRetcode;
    }
  }
