switch (pBuftarget->iBitdepth)
                        {
#ifndef MNG_NO_1_2_4BIT_SUPPORT
                          case  1 : { pData->fDeltarow = (mng_fptr)mng_delta_g1_g1; break; }
                          case  2 : { pData->fDeltarow = (mng_fptr)mng_delta_g2_g2; break; }
                          case  4 : { pData->fDeltarow = (mng_fptr)mng_delta_g4_g4; break; }
#endif /* MNG_NO_1_2_4BIT_SUPPORT */
                          case  8 : { pData->fDeltarow = (mng_fptr)mng_delta_g8_g8; break; }
                        }
