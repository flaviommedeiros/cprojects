if (state.Probs == 0 
    #ifdef _LZMA_OUT_READ
    || (state.Dictionary == 0 && state.Properties.DictionarySize != 0)
    #else
    || (outStream == 0 && outSizeFull != 0)
    #endif
    #ifndef _LZMA_IN_CB
    || (inStream == 0 && compressedSize != 0)
    #endif
    )
  {
    free(state.Probs);
    #ifdef _LZMA_OUT_READ
    free(state.Dictionary);
    #else
    free(outStream);
    #endif
    #ifndef _LZMA_IN_CB
    free(inStream);
    #endif
    return PrintError(rs, kCantAllocateMessage);
  }
