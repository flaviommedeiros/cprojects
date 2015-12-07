#ifdef MNG_INCLUDE_JNG
if (pData->bHasJHDR)
  {
    pBuf->bHasBKGD = MNG_TRUE;         /* tell the object it's got bKGD now */

    switch (pData->iJHDRcolortype)     /* store fields for future reference */
    {
      case  8 : ;                      /* gray */
      case 12 : {                      /* graya */
                  pBuf->iBKGDgray  = ((mng_bkgdp)pChunk)->iGray;
                  break;
                }
      case 10 : ;                      /* rgb */
      case 14 : {                      /* rgba */
                  pBuf->iBKGDred   = ((mng_bkgdp)pChunk)->iRed;
                  pBuf->iBKGDgreen = ((mng_bkgdp)pChunk)->iGreen;
                  pBuf->iBKGDblue  = ((mng_bkgdp)pChunk)->iBlue;
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
                 pBuf->iBKGDgray  = ((mng_bkgdp)pChunk)->iGray;
                 break;
               }
      case 2 : ;                        /* rgb */
      case 6 : {                        /* rgba */
                 pBuf->iBKGDred   = ((mng_bkgdp)pChunk)->iRed;
                 pBuf->iBKGDgreen = ((mng_bkgdp)pChunk)->iGreen;
                 pBuf->iBKGDblue  = ((mng_bkgdp)pChunk)->iBlue;
                 break;
               }
      case 3 : {                        /* indexed */
                 pBuf->iBKGDindex = ((mng_bkgdp)pChunk)->iIndex;
                 break;
               }
    }
  }
  else                                 /* store as global */
  {
    if (!(((mng_bkgdp)pChunk)->bEmpty))
    {
      pData->iGlobalBKGDred   = ((mng_bkgdp)pChunk)->iRed;
      pData->iGlobalBKGDgreen = ((mng_bkgdp)pChunk)->iGreen;
      pData->iGlobalBKGDblue  = ((mng_bkgdp)pChunk)->iBlue;
    }
                                       /* create an animation object */
    return mng_create_ani_bkgd (pData);
  }
