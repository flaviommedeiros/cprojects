#ifdef MNG_STORE_CHUNKS
if (pData->bStorechunks)
  {                                    /* initialize storage */
    mng_retcode iRetcode = ((mng_chunk_headerp)pHeader)->fCreate (pData, pHeader, ppChunk);

    if (iRetcode)                      /* on error bail out */
      return iRetcode;
                                       /* store the fields */
    ((mng_basip)*ppChunk)->iWidth       = mng_get_uint32 (pRawdata);
    ((mng_basip)*ppChunk)->iHeight      = mng_get_uint32 (pRawdata+4);
#ifdef MNG_NO_16BIT_SUPPORT
    if (*(pRawdata+8) > 8)
      ((mng_basip)*ppChunk)->iBitdepth    = 8;
    else
#endif
      ((mng_basip)*ppChunk)->iBitdepth    = *(pRawdata+8);
    ((mng_basip)*ppChunk)->iColortype   = *(pRawdata+9);
    ((mng_basip)*ppChunk)->iCompression = *(pRawdata+10);
    ((mng_basip)*ppChunk)->iFilter      = *(pRawdata+11);
    ((mng_basip)*ppChunk)->iInterlace   = *(pRawdata+12);

    if (iRawlen > 13)
    {
      ((mng_basip)*ppChunk)->iRed       = mng_get_uint16 (pRawdata+13);
      ((mng_basip)*ppChunk)->iGreen     = mng_get_uint16 (pRawdata+15);
      ((mng_basip)*ppChunk)->iBlue      = mng_get_uint16 (pRawdata+17);
    }

    if (iRawlen > 19)
      ((mng_basip)*ppChunk)->iAlpha     = mng_get_uint16 (pRawdata+19);

    if (iRawlen > 21)
      ((mng_basip)*ppChunk)->iViewable  = *(pRawdata+21);

  }
