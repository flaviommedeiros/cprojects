#ifndef MNG_OPTIMIZE_DISPLAYCALLS
if ((bHasalpha) && (!iAlpha))
#else
               if ((pData->bBASIhasalpha) && (!pData->iBASIalpha))
#endif
               {
                 pBuf->bHasTRNS   = MNG_TRUE;
#ifndef MNG_OPTIMIZE_DISPLAYCALLS
                 pBuf->iTRNSred   = iRed;
                 pBuf->iTRNSgreen = iGreen;
                 pBuf->iTRNSblue  = iBlue;
#else
                 pBuf->iTRNSred   = pData->iBASIred;
                 pBuf->iTRNSgreen = pData->iBASIgreen;
                 pBuf->iTRNSblue  = pData->iBASIblue;
#endif
               }
