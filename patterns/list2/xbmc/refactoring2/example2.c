#ifdef MNG_STORE_CHUNKS
if (!pData->bStorechunks)
#endif
      {
        iRetcode = ((mng_chunk_headerp)*ppChunk)->fCleanup (pData, *ppChunk);
        if (iRetcode)                  /* on error bail out */
          return iRetcode;
        *ppChunk = MNG_NULL;
      }
