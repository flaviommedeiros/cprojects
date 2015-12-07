#if defined(MNG_STORE_CHUNKS) || defined(MNG_SUPPORT_DISPLAY)
if (!pData->bHasMHDR)                /* sequence checks */
    MNG_ERROR (pData, MNG_SEQUENCEERROR);
