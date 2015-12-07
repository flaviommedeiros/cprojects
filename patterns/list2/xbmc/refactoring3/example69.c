switch (pBuftarget->iBitdepth)
                    {
                      case  2 : { pData->fScalerow = (mng_fptr)mng_scale_g1_g2;  break; }
                      case  4 : { pData->fScalerow = (mng_fptr)mng_scale_g1_g4;  break; }

                      case  8 : { pData->fScalerow = (mng_fptr)mng_scale_g1_g8;  break; }
#ifndef MNG_NO_16BIT_SUPPORT
                      case 16 : { pData->fScalerow = (mng_fptr)mng_scale_g1_g16; break; }
#endif
                    }
