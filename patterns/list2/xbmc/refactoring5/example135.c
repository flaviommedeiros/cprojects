#ifndef MNG_NO_OLD_VERSIONS
if (pData->bPreDraft48)
    {
      iTermination = *(pRawdata+1);

      iRepeat = mng_get_uint32 (pRawdata+2);
    }
    else
#endif
      iRepeat = mng_get_uint32 (pRawdata+1);
