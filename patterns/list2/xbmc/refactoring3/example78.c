switch (pBuftarget->iBitdepth)
                        {
                          case  8 : { pData->fDeltarow = (mng_fptr)mng_delta_rgb8_rgb8;   break; }
#ifndef MNG_NO_16BIT_SUPPORT
                          case 16 : { pData->fDeltarow = (mng_fptr)mng_delta_rgb16_rgb16; break; }
#endif
                        }
