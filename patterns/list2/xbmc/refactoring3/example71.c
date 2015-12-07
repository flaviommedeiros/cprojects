switch (pBuftarget->iBitdepth)
                    {
                      case  1 : { pData->fScalerow = (mng_fptr)mng_scale_g4_g1;  break; }
                      case  2 : { pData->fScalerow = (mng_fptr)mng_scale_g4_g2;  break; }
                      case  8 : { pData->fScalerow = (mng_fptr)mng_scale_g4_g8;  break; }
#ifndef MNG_NO_16BIT_SUPPORT
                      case 16 : { pData->fScalerow = (mng_fptr)mng_scale_g4_g16; break; }
#endif
                    }
