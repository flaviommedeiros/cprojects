#ifdef MNG_INCLUDE_JNG
if ((!pData->bHasMHDR) && (!pData->bHasIHDR) && (!pData->bHasJHDR))
#else
  if ((!pData->bHasMHDR) && (!pData->bHasIHDR))
#endif
    iRetcode = mng_process_eof (pData);
