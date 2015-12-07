#ifdef MNG_SUPPORT_TRACE
if ((!pData->bHasMHDR) || (pData->bHasIHDR) || (pData->bHasDHDR) || (pData->bHasJHDR))
#else
  if ((!pData->bHasMHDR) || (pData->bHasIHDR) || (pData->bHasDHDR))
#endif
    MNG_ERROR (pData, MNG_SEQUENCEERROR);
