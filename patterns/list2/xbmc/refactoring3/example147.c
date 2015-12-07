switch (iBitdepth)
                   {
                     case  8 : { pData->fPromBitdepth = (mng_fptr)mng_promote_zerofill_4_8;  break; }
#ifndef MNG_NO_16BIT_SUPPORT
                     case 16 : { pData->fPromBitdepth = (mng_fptr)mng_promote_zerofill_4_16; break; }
#endif
                   }
