#ifdef _LZMA_OUT_READ
if (rep0 > distanceLimit) 
      #else
      if (rep0 > nowPos)
      #endif
        return LZMA_RESULT_DATA_ERROR;
