switch (iBitdepth)
                   {
                     case  2 : { pData->fPromBitdepth = (mng_fptr)mng_promote_zerofill_1_2;  break; }
                     case  4 : { pData->fPromBitdepth = (mng_fptr)mng_promote_zerofill_1_4;  break; }
                     case  8 : { pData->fPromBitdepth = (mng_fptr)mng_promote_zerofill_1_8;  break; }
#ifndef MNG_NO_16BIT_SUPPORT
                     case 16 : { pData->fPromBitdepth = (mng_fptr)mng_promote_zerofill_1_16; break; }
#endif
                   }
