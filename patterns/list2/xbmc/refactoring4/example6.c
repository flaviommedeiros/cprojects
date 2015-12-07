#ifdef MNG_SUPPORT_TRACE
if (!pData->pDeltaImage)             /* gotta have this now! */
    MNG_ERROR (pData, MNG_INVALIDDELTA);
