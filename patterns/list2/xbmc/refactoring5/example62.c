#ifndef MNG_NO_16BIT_SUPPORT
if (pBuf->iBitdepth > 8)
               {
                 iRed   = (mng_uint8)(pBuf->iBKGDred   >> 8);
                 iGreen = (mng_uint8)(pBuf->iBKGDgreen >> 8);
                 iBlue  = (mng_uint8)(pBuf->iBKGDblue  >> 8);
               }
               else
#endif
               {
                 iRed   = (mng_uint8)(pBuf->iBKGDred  );
                 iGreen = (mng_uint8)(pBuf->iBKGDgreen);
                 iBlue  = (mng_uint8)(pBuf->iBKGDblue );
               }
