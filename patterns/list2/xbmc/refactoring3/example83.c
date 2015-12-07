switch (pBuftarget->iBitdepth)
                        {
                          case  8 : { pData->fDeltarow = (mng_fptr)mng_delta_rgba8_rgba8;   break; }
#ifndef MNG_NO_16BIT_SUPPORT
                          case 16 : { pData->fDeltarow = (mng_fptr)mng_delta_rgba16_rgba16; break; }
#endif
                        }
