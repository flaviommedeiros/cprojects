if ((pData->iBitdepth !=  8)      /* parameter validity checks */
#ifndef MNG_NO_1_2_4BIT_SUPPORT
      && (pData->iBitdepth !=  1) &&
      (pData->iBitdepth !=  2) &&
      (pData->iBitdepth !=  4)
#endif
#ifndef MNG_NO_16BIT_SUPPORT
      && (pData->iBitdepth != 16)   
#endif
      )
    MNG_ERROR (pData, MNG_INVALIDBITDEPTH);
