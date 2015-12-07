#ifdef MNG_SUPPORT_TRACE
if ((pBuf->iBitdepth < 8) ||         /* we need 8- or 16-bit RGBA !!! */
      ((pBuf->iColortype != MNG_COLORTYPE_RGBA      ) &&
       (pBuf->iColortype != MNG_COLORTYPE_JPEGCOLORA)    ))
#else
  if (pBuf->iBitdepth < 8)         /* we need 8- or 16-bit RGBA !!! */
#endif
    MNG_ERROR (pData, MNG_OBJNOTABSTRACT);
