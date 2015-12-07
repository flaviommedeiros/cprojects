#ifdef MNG_STORE_CHUNKS
if (pData->bStorechunks)
  {                                    /* initialize storage */
    mng_retcode iRetcode = ((mng_chunk_headerp)pHeader)->fCreate (pData, pHeader, ppChunk);

    if (iRetcode)                      /* on error bail out */
      return iRetcode;
                                       /* store the fields */
    ((mng_sbitp)*ppChunk)->bEmpty = (mng_bool)(iRawlen == 0);

    if (iRawlen)
    {
#ifdef MNG_INCLUDE_JNG
      if (pData->bHasJHDR)
        ((mng_sbitp)*ppChunk)->iType = pData->iJHDRcolortype;
      else
#endif
      if (pData->bHasIHDR)
        ((mng_sbitp)*ppChunk)->iType = pData->iColortype;
      else                             /* global ! */
        ((mng_sbitp)*ppChunk)->iType = 6;

      if (iRawlen > 0)
        ((mng_sbitp)*ppChunk)->aBits [0] = *pRawdata;
      if (iRawlen > 1)
        ((mng_sbitp)*ppChunk)->aBits [1] = *(pRawdata+1);
      if (iRawlen > 2)
        ((mng_sbitp)*ppChunk)->aBits [2] = *(pRawdata+2);
      if (iRawlen > 3)
        ((mng_sbitp)*ppChunk)->aBits [3] = *(pRawdata+3);

    }
  }
