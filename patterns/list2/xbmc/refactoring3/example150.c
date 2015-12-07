switch (iBitdepth)
                   {
                     case  4 : { pData->fPromBitdepth = (mng_fptr)mng_promote_replicate_2_4;  break; }
                     case  8 : { pData->fPromBitdepth = (mng_fptr)mng_promote_replicate_2_8;  break; }
#ifndef MNG_NO_16BIT_SUPPORT
                     case 16 : { pData->fPromBitdepth = (mng_fptr)mng_promote_replicate_2_16; break; }
#endif
                   }
