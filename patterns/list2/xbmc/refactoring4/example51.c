#ifdef MNG_SUPPORT_TRACE
if (pData->eSigtype != mng_it_mng)   /* sequence checks */
    MNG_ERROR (pData, MNG_CHUNKNOTALLOWED);
