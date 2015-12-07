switch (pBuftarget->iBitdepth)
                        {
                          case  8 : { pData->fDeltarow = (mng_fptr)mng_delta_ga8_g8;   break; }
#ifndef MNG_NO_16BIT_SUPPORT
                          case 16 : { pData->fDeltarow = (mng_fptr)mng_delta_ga16_g16; break; }
#endif
                        }
