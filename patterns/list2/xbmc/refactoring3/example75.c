switch (pBuftarget->iBitdepth)
                                  {
#ifndef MNG_NO_1_2_4BIT_SUPPORT
                                    case 1 : { pData->fScalerow = (mng_fptr)mng_scale_g16_g1; break; }
                                    case 2 : { pData->fScalerow = (mng_fptr)mng_scale_g16_g2; break; }
                                    case 4 : { pData->fScalerow = (mng_fptr)mng_scale_g16_g4; break; }
#endif /* MNG_NO_1_2_4BIT_SUPPORT */
                                    case 8 : { pData->fScalerow = (mng_fptr)mng_scale_g16_g8; break; }
                                  }
