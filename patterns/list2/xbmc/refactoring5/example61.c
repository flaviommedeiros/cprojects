#ifndef MNG_NO_16BIT_SUPPORT
if (pBuf->iBitdepth > 8)
                 iGray = (mng_uint8)(pBuf->iBKGDgray >> 8);
               else
#endif
               {
#ifndef MNG_NO_1_2_4BIT_SUPPORT
                 /* LBR scaling */
                 mng_uint8 multiplier[]={0,255,85,0,17,0,0,0,1};
                 iGray = (mng_uint8)(multiplier[pBuf->iBitdepth] * pBuf->iBKGDgray);
#else
                 iGray = (mng_uint8)pBuf->iBKGDgray;
#endif
               }
