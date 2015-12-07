if ((((mng_promp)pChunk)->iSampledepth != MNG_BITDEPTH_1 ) &&
      (((mng_promp)pChunk)->iSampledepth != MNG_BITDEPTH_2 ) &&
      (((mng_promp)pChunk)->iSampledepth != MNG_BITDEPTH_4 ) &&
      (((mng_promp)pChunk)->iSampledepth != MNG_BITDEPTH_8 )
#ifndef MNG_NO_16BIT_SUPPORT
      && (((mng_promp)pChunk)->iSampledepth != MNG_BITDEPTH_16)
#endif
    )
    MNG_ERROR (pData, MNG_INVSAMPLEDEPTH);
