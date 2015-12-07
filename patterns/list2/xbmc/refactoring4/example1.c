#ifdef MNG_SUPPORT_DYNAMICMNG
if ((!pData->bDynamic) || (pData->bRunning))
#else
  if (pData->bRunning)
#endif
    pData->bTimerset = MNG_TRUE;
