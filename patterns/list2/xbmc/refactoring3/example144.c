switch (iTempdepth)
      {
#ifndef MNG_NO_1_2_4BIT_SUPPORT
        case 1 : {
                   switch (iBitdepth)
                   {
                     case  2 : { pData->fPromBitdepth = (mng_fptr)mng_promote_zerofill_1_2;  break; }
                     case  4 : { pData->fPromBitdepth = (mng_fptr)mng_promote_zerofill_1_4;  break; }
                     case  8 : { pData->fPromBitdepth = (mng_fptr)mng_promote_zerofill_1_8;  break; }
#ifndef MNG_NO_16BIT_SUPPORT
                     case 16 : { pData->fPromBitdepth = (mng_fptr)mng_promote_zerofill_1_16; break; }
#endif
                   }
                   break;
                 }
        case 2 : {
                   switch (iBitdepth)
                   {
                     case  4 : { pData->fPromBitdepth = (mng_fptr)mng_promote_zerofill_2_4;  break; }
                     case  8 : { pData->fPromBitdepth = (mng_fptr)mng_promote_zerofill_2_8;  break; }
#ifndef MNG_NO_16BIT_SUPPORT
                     case 16 : { pData->fPromBitdepth = (mng_fptr)mng_promote_zerofill_2_16; break; }
#endif
                   }
                   break;
                 }
        case 4 : {
                   switch (iBitdepth)
                   {
                     case  8 : { pData->fPromBitdepth = (mng_fptr)mng_promote_zerofill_4_8;  break; }
#ifndef MNG_NO_16BIT_SUPPORT
                     case 16 : { pData->fPromBitdepth = (mng_fptr)mng_promote_zerofill_4_16; break; }
#endif
                   }
                   break;
                 }
#endif /* MNG_NO_1_2_4BIT_SUPPORT */
        case 8 : {
#ifndef MNG_NO_16BIT_SUPPORT
                   if (iBitdepth == 16)
                     pData->fPromBitdepth = (mng_fptr)mng_promote_zerofill_8_16;
#endif
                   break;
                 }
      }
