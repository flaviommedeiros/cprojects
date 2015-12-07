#ifdef MNG_SUPPORT_DISPLAY
if ((!pData->bHasMHDR) && (!pData->bHasIHDR) &&
      (!pData->bHasBASI) && (!pData->bHasDHDR) && (!pData->bHasJHDR))
#else
  if ((!pData->bHasMHDR) && (!pData->bHasIHDR) &&
      (!pData->bHasBASI) && (!pData->bHasDHDR)    )
#endif
    MNG_ERROR (pData, MNG_SEQUENCEERROR);
