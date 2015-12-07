switch (pBuftarget->iBitdepth)
                        {
                          case  8 : { pData->fDeltarow = (mng_fptr)mng_delta_ga8_a8;   break; }
#ifndef MNG_NO_16BIT_SUPPORT
                          case 16 : { pData->fDeltarow = (mng_fptr)mng_delta_ga16_a16; break; }
#endif
                        }
