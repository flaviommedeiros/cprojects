#ifdef MNG_INCLUDE_JNG
if ((pData->iFirstchunkadded == MNG_UINT_IHDR) ||
      (pData->iFirstchunkadded == MNG_UINT_JHDR)    )
#else
  if (pData->iFirstchunkadded == MNG_UINT_IHDR)
#endif
    pData->bCreating = MNG_FALSE;
