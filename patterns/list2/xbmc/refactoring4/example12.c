#ifdef MNG_SUPPORT_TRACE
if ((pData->bReading) || (pData->bDisplaying))
#else
  if (pData->bReading)
#endif
    MNG_ERROR (pData, MNG_FUNCTIONINVALID);
