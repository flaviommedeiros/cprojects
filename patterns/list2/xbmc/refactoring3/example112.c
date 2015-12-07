switch (pData->iBitdepth)
                   {
#ifndef MNG_NO_1_2_4BIT_SUPPORT
                     case  1 : {
                                 if (!pData->iInterlace)
                                   pData->fInitrowproc = (mng_fptr)mng_init_g1_ni;
                                 else
                                   pData->fInitrowproc = (mng_fptr)mng_init_g1_i;

                                 break;
                               }
                     case  2 : {
                                 if (!pData->iInterlace)
                                   pData->fInitrowproc = (mng_fptr)mng_init_g2_ni;
                                 else
                                   pData->fInitrowproc = (mng_fptr)mng_init_g2_i;

                                 break;
                               }
                     case  4 : {
                                 if (!pData->iInterlace)
                                   pData->fInitrowproc = (mng_fptr)mng_init_g4_ni;
                                 else
                                   pData->fInitrowproc = (mng_fptr)mng_init_g4_i;

                                 break;
                               }
#endif /* MNG_NO_1_2_4BIT_SUPPORT */
                     case  8 : {
                                 if (!pData->iInterlace)
                                   pData->fInitrowproc = (mng_fptr)mng_init_g8_ni;
                                 else
                                   pData->fInitrowproc = (mng_fptr)mng_init_g8_i;

                                 break;
                               }
#ifndef MNG_NO_16BIT_SUPPORT
                     case 16 : {
                                 if (!pData->iInterlace)
                                   pData->fInitrowproc = (mng_fptr)mng_init_g16_ni;
                                 else
                                   pData->fInitrowproc = (mng_fptr)mng_init_g16_i;

                                 break;
                               }
#endif
                   }
