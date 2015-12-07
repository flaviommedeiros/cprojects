#ifdef MNG_STORE_CHUNKS
if (pData->bStorechunks)
  {                                    /* initialize storage */
    mng_retcode iRetcode = ((mng_chunk_headerp)pHeader)->fCreate (pData, pHeader, ppChunk);

    if (iRetcode)                      /* on error bail out */
      return iRetcode;

    if (iRawlen >= 5)                  /* store the fields */
    {
      ((mng_loopp)*ppChunk)->iLevel  = *pRawdata;

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

      if (iRawlen >= 6)
      {
#ifndef MNG_NO_OLD_VERSIONS
        if (!pData->bPreDraft48)
#endif
          ((mng_loopp)*ppChunk)->iTermination = *(pRawdata+5);

        if (iRawlen >= 10)
        {
          ((mng_loopp)*ppChunk)->iItermin = mng_get_uint32 (pRawdata+6);

#ifndef MNG_NO_LOOP_SIGNALS_SUPPORTED
          if (iRawlen >= 14)
          {
            ((mng_loopp)*ppChunk)->iItermax = mng_get_uint32 (pRawdata+10);
            ((mng_loopp)*ppChunk)->iCount   = (iRawlen - 14) / 4;

            if (((mng_loopp)*ppChunk)->iCount)
            {
              MNG_ALLOC (pData, ((mng_loopp)*ppChunk)->pSignals,
                                ((mng_loopp)*ppChunk)->iCount << 2);

#ifndef MNG_BIGENDIAN_SUPPORTED
              {
                mng_uint32  iX;
                mng_uint8p  pIn  = pRawdata + 14;
                mng_uint32p pOut = (mng_uint32p)((mng_loopp)*ppChunk)->pSignals;

                for (iX = 0; iX < ((mng_loopp)*ppChunk)->iCount; iX++)
                {
                  *pOut++ = mng_get_uint32 (pIn);
                  pIn += 4;
                }
              }
#else
              MNG_COPY (((mng_loopp)*ppChunk)->pSignals, pRawdata + 14,
                        ((mng_loopp)*ppChunk)->iCount << 2);
#endif /* !MNG_BIGENDIAN_SUPPORTED */
            }
          }
#endif
        }
      }
    }
  }
