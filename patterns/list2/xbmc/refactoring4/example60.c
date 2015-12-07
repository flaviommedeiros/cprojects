#if defined(MNG_SUPPORT_DISPLAY) || defined(MNG_STORE_CHUNKS)
if (!pData->bHasMHDR)                /* sequence checks */
    MNG_ERROR (pData, MNG_SEQUENCEERROR);
