switch (pData->iBitdepth)
                 {
#ifndef MNG_NO_1_2_4BIT_SUPPORT
                   case  1 : {
                               if (!pData->iInterlace)
                                 pData->fInitrowproc = (mng_fptr)mng_init_idx1_ni;
                               else
                                 pData->fInitrowproc = (mng_fptr)mng_init_idx1_i;

                               break;
                             }
                   case  2 : {
                               if (!pData->iInterlace)
                                 pData->fInitrowproc = (mng_fptr)mng_init_idx2_ni;
                               else
                                 pData->fInitrowproc = (mng_fptr)mng_init_idx2_i;

                               break;
                             }
                   case  4 : {
                               if (!pData->iInterlace)
                                 pData->fInitrowproc = (mng_fptr)mng_init_idx4_ni;
                               else
                                 pData->fInitrowproc = (mng_fptr)mng_init_idx4_i;

                               break;
                             }
#endif /* MNG_NO_1_2_4BIT_SUPPORT */
                   case  8 : {
                               if (!pData->iInterlace)
                                 pData->fInitrowproc = (mng_fptr)mng_init_idx8_ni;
                               else
                                 pData->fInitrowproc = (mng_fptr)mng_init_idx8_i;

                               break;
                             }
                 }
