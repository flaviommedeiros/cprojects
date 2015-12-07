#ifdef MNG_INCLUDE_JNG
if (pData->bHasJHDR)
        ((mng_sbitp)*ppChunk)->iType = pData->iJHDRcolortype;
      else
#endif
      if (pData->bHasIHDR)
        ((mng_sbitp)*ppChunk)->iType = pData->iColortype;
      else                             /* global ! */
        ((mng_sbitp)*ppChunk)->iType = 6;
