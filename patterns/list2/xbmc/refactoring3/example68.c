switch (pBufdelta->iBitdepth)    /* determine scaling routine */
      {
#ifndef MNG_NO_1_2_4BIT_SUPPORT
        case  1 : {
                    switch (pBuftarget->iBitdepth)
                    {
                      case  2 : { pData->fScalerow = (mng_fptr)mng_scale_g1_g2;  break; }
                      case  4 : { pData->fScalerow = (mng_fptr)mng_scale_g1_g4;  break; }

                      case  8 : { pData->fScalerow = (mng_fptr)mng_scale_g1_g8;  break; }
#ifndef MNG_NO_16BIT_SUPPORT
                      case 16 : { pData->fScalerow = (mng_fptr)mng_scale_g1_g16; break; }
#endif
                    }
                    break;
                  }

        case  2 : {
                    switch (pBuftarget->iBitdepth)
                    {
                      case  1 : { pData->fScalerow = (mng_fptr)mng_scale_g2_g1;  break; }
                      case  4 : { pData->fScalerow = (mng_fptr)mng_scale_g2_g4;  break; }
                      case  8 : { pData->fScalerow = (mng_fptr)mng_scale_g2_g8;  break; }
#ifndef MNG_NO_16BIT_SUPPORT
                      case 16 : { pData->fScalerow = (mng_fptr)mng_scale_g2_g16; break; }
#endif
                    }
                    break;
                  }

        case  4 : {
                    switch (pBuftarget->iBitdepth)
                    {
                      case  1 : { pData->fScalerow = (mng_fptr)mng_scale_g4_g1;  break; }
                      case  2 : { pData->fScalerow = (mng_fptr)mng_scale_g4_g2;  break; }
                      case  8 : { pData->fScalerow = (mng_fptr)mng_scale_g4_g8;  break; }
#ifndef MNG_NO_16BIT_SUPPORT
                      case 16 : { pData->fScalerow = (mng_fptr)mng_scale_g4_g16; break; }
#endif
                    }
                    break;
                  }
#endif /* MNG_NO_1_2_4BIT_SUPPORT */

        case  8 : {
                    switch (pBufdelta->iColortype)
                    {
                      case  0 : ;
                      case  3 : ;
                      case  8 : {
                                  switch (pBuftarget->iBitdepth)
                                  {
#ifndef MNG_NO_1_2_4BIT_SUPPORT
                                    case  1 : { pData->fScalerow = (mng_fptr)mng_scale_g8_g1;  break; }
                                    case  2 : { pData->fScalerow = (mng_fptr)mng_scale_g8_g2;  break; }
                                    case  4 : { pData->fScalerow = (mng_fptr)mng_scale_g8_g4;  break; }
#endif /* MNG_NO_1_2_4BIT_SUPPORT */
#ifndef MNG_NO_16BIT_SUPPORT
                                    case 16 : { pData->fScalerow = (mng_fptr)mng_scale_g8_g16; break; }
#endif
                                  }
                                  break;
                                }
                      case  2 : ;
                      case 10 : {
#ifndef MNG_NO_16BIT_SUPPORT
                                  if (pBuftarget->iBitdepth == 16)
                                    pData->fScalerow = (mng_fptr)mng_scale_rgb8_rgb16;
#endif
                                  break;
                                }
                      case  4 : ;
                      case 12 : {
#ifndef MNG_NO_16BIT_SUPPORT
                                  if (pBuftarget->iBitdepth == 16)
                                    pData->fScalerow = (mng_fptr)mng_scale_ga8_ga16;
#endif
                                  break;
                                }
                      case  6 : ;
                      case 14 : {
#ifndef MNG_NO_16BIT_SUPPORT
                                  if (pBuftarget->iBitdepth == 16)
                                    pData->fScalerow = (mng_fptr)mng_scale_rgba8_rgba16;
#endif
                                  break;
                                }
                    }
                    break;
                  }

#ifndef MNG_NO_16BIT_SUPPORT
        case 16 : {
                    switch (pBufdelta->iColortype)
                    {
                      case  0 : ;
                      case  3 : ;
                      case  8 : {
                                  switch (pBuftarget->iBitdepth)
                                  {
#ifndef MNG_NO_1_2_4BIT_SUPPORT
                                    case 1 : { pData->fScalerow = (mng_fptr)mng_scale_g16_g1; break; }
                                    case 2 : { pData->fScalerow = (mng_fptr)mng_scale_g16_g2; break; }
                                    case 4 : { pData->fScalerow = (mng_fptr)mng_scale_g16_g4; break; }
#endif /* MNG_NO_1_2_4BIT_SUPPORT */
                                    case 8 : { pData->fScalerow = (mng_fptr)mng_scale_g16_g8; break; }
                                  }
                                  break;
                                }
                      case  2 : ;
                      case 10 : {
                                  if (pBuftarget->iBitdepth == 8)
                                    pData->fScalerow = (mng_fptr)mng_scale_rgb16_rgb8;
                                  break;
                                }
                      case  4 : ;
                      case 12 : {
                                  if (pBuftarget->iBitdepth == 8)
                                    pData->fScalerow = (mng_fptr)mng_scale_ga16_ga8;
                                  break;
                                }
                      case  6 : ;
                      case 14 : {
                                  if (pBuftarget->iBitdepth == 8)
                                    pData->fScalerow = (mng_fptr)mng_scale_rgba16_rgba8;
                                  break;
                                }
                    }
                    break;
                  }
#endif

      }
