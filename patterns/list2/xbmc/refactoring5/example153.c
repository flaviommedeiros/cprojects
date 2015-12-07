#ifndef MNG_NO_OLD_VERSIONS
if (pData->bPreDraft48)
    {
      pLOOP->iTermination = *(pRawdata+1);
      pLOOP->iRepeat = mng_get_uint32 (pRawdata+2);
    }
    else
#endif
    {
      pLOOP->iRepeat = mng_get_uint32 (pRawdata+1);
    }
