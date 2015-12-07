#ifdef MNG_INCLUDE_JNG
if ((pDataOut->iFirstchunkadded == MNG_UINT_IHDR) ||
        (pDataOut->iFirstchunkadded == MNG_UINT_JHDR)    )
#else
    if (pDataOut->iFirstchunkadded == MNG_UINT_IHDR)
#endif
      pDataOut->bCreating = MNG_FALSE;
