#ifdef MNG_SUPPORT_TRACE
if ((!pData->bHasMHDR) && (!pData->bHasIHDR) &&
      (!pData->bHasBASI) && (!pData->bHasDHDR)    )
    MNG_ERROR (pData, MNG_SEQUENCEERROR);
