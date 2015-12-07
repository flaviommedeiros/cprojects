#ifdef MNG_SUPPORT_TRACE
if ((!pData->bHasMHDR) || (!pData->bHasSAVE))
    MNG_ERROR (pData, MNG_SEQUENCEERROR);
