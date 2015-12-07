#ifndef MNG_OPTIMIZE_DISPLAYCALLS
if ((bHasalpha) && (iAlpha < 255))
#else
               if ((pData->bBASIhasalpha) && (pData->iBASIalpha < 255))
#endif
               {
                 pBuf->bHasTRNS         = MNG_TRUE;
                 pBuf->iTRNScount       = 1;
#ifndef MNG_OPTIMIZE_DISPLAYCALLS
                 pBuf->aTRNSentries [0] = (mng_uint8)iAlpha;
#else
                 pBuf->aTRNSentries [0] = (mng_uint8)pData->iBASIalpha;
#endif
               }
