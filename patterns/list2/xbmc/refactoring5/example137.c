#ifndef MNG_NO_OLD_VERSIONS
if (pData->bPreDraft48)
      {
        ((mng_loopp)*ppChunk)->iTermination = *(pRawdata+1);
        ((mng_loopp)*ppChunk)->iRepeat = mng_get_uint32 (pRawdata+2);
      }
      else
#endif
      {
        ((mng_loopp)*ppChunk)->iRepeat = mng_get_uint32 (pRawdata+1);
      }
