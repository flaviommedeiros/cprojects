#ifdef MNG_NO_16BIT_SUPPORT
if (*(pRawdata+8) > 8)
      ((mng_basip)*ppChunk)->iBitdepth    = 8;
    else
#endif
      ((mng_basip)*ppChunk)->iBitdepth    = *(pRawdata+8);
