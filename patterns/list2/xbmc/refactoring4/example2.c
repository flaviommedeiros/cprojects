#ifndef MNG_OPTIMIZE_DISPLAYCALLS
if ((bHasalpha) && (!iAlpha))
#else
               if ((pData->bBASIhasalpha) && (!pData->iBASIalpha))
#endif
               {
                 pBuf->bHasTRNS  = MNG_TRUE;
#ifndef MNG_OPTIMIZE_DISPLAYCALLS
                 pBuf->iTRNSgray = iRed;
#else
                 pBuf->iTRNSgray = pData->iBASIred;
#endif
               }
