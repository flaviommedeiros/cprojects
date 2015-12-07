switch (iTempdepth)
      {
#ifndef MNG_NO_1_2_4BIT_SUPPORT
        case 1 : {
                   switch (iBitdepth)
                   {
                     case  2 : { pData->fPromBitdepth = (mng_fptr)mng_promote_replicate_1_2;  break; }
                     case  4 : { pData->fPromBitdepth = (mng_fptr)mng_promote_replicate_1_4;  break; }
                     case  8 : { pData->fPromBitdepth = (mng_fptr)mng_promote_replicate_1_8;  break; }
#ifndef MNG_NO_16BIT_SUPPORT
                     case 16 : { pData->fPromBitdepth = (mng_fptr)mng_promote_replicate_1_16; break; }
#endif
                   }
                   break;
                 }
        case 2 : {
                   switch (iBitdepth)
                   {
                     case  4 : { pData->fPromBitdepth = (mng_fptr)mng_promote_replicate_2_4;  break; }
                     case  8 : { pData->fPromBitdepth = (mng_fptr)mng_promote_replicate_2_8;  break; }
#ifndef MNG_NO_16BIT_SUPPORT
                     case 16 : { pData->fPromBitdepth = (mng_fptr)mng_promote_replicate_2_16; break; }
#endif
                   }
                   break;
                 }
        case 4 : {
                   switch (iBitdepth)
                   {
                     case  8 : { pData->fPromBitdepth = (mng_fptr)mng_promote_replicate_4_8;  break; }
#ifndef MNG_NO_16BIT_SUPPORT
                     case 16 : { pData->fPromBitdepth = (mng_fptr)mng_promote_replicate_4_16; break; }
#endif
                   }
                   break;
                 }
#endif /* MNG_NO_1_2_4BIT_SUPPORT */
        case 8 : {
#ifndef MNG_NO_16BIT_SUPPORT
                   if (iBitdepth == 16)
                     pData->fPromBitdepth = (mng_fptr)mng_promote_replicate_8_16;
#endif
                   break;
                 }
      }
