switch (pData->iBitdepth)
               {
                 case  8 : {
                             if (!pData->iInterlace)
                               pData->fInitrowproc = (mng_fptr)mng_init_rgba8_ni;
                             else
                               pData->fInitrowproc = (mng_fptr)mng_init_rgba8_i;

                             break;
                           }
#ifndef MNG_NO_16BIT_SUPPORT
                 case 16 : {
                             if (!pData->iInterlace)
                               pData->fInitrowproc = (mng_fptr)mng_init_rgba16_ni;
                             else
                               pData->fInitrowproc = (mng_fptr)mng_init_rgba16_i;

                             break;
                           }
#endif
               }
