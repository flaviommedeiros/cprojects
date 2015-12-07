#if defined(MNG_SUPPORT_DISPLAY) || defined(MNG_STORE_CHUNKS)
if ((!pData->bHasMHDR) && (!pData->bHasIHDR) &&
      (!pData->bHasBASI) && (!pData->bHasDHDR)    )
    MNG_ERROR (pData, MNG_SEQUENCEERROR);
