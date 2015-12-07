if ((pData->iJHDRalphabitdepth != MNG_BITDEPTH_8 )
#ifndef MNG_NO_1_2_4BIT_SUPPORT
        && (pData->iJHDRalphabitdepth != MNG_BITDEPTH_1 ) &&
        (pData->iJHDRalphabitdepth != MNG_BITDEPTH_2 ) &&
        (pData->iJHDRalphabitdepth != MNG_BITDEPTH_4 )
#endif
#ifndef MNG_NO_16BIT_SUPPORT
        && (pData->iJHDRalphabitdepth != MNG_BITDEPTH_16)
#endif
        )
      MNG_ERROR (pData, MNG_INVALIDBITDEPTH);
