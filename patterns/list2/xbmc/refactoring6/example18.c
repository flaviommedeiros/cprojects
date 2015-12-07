if ((iSampledepth != MNG_BITDEPTH_1 ) &&
      (iSampledepth != MNG_BITDEPTH_2 ) &&
      (iSampledepth != MNG_BITDEPTH_4 ) &&
      (iSampledepth != MNG_BITDEPTH_8 )
#ifndef MNG_NO_16BIT_SUPPORT
      && (iSampledepth != MNG_BITDEPTH_16)
#endif
    )
    MNG_ERROR (pData, MNG_INVSAMPLEDEPTH);
