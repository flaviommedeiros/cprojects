#ifdef MNG_INCLUDE_JNG
if (pData->iSimplicity & 0x0000FC00)
#else
  if (pData->iSimplicity & 0x0000FC10)
#endif
    MNG_ERROR (pData, MNG_MNGTOOCOMPLEX);
