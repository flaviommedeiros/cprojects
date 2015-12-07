#ifdef MNG_SUPPORT_TRACE
if (!pData->bHasMHDR)                /* sequence checks */
    MNG_ERROR (pData, MNG_SEQUENCEERROR);
