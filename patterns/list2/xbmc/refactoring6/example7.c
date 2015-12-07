if ( ((pBuf->iColortype == MNG_COLORTYPE_GRAY      ) &&
        (iColortype       != MNG_COLORTYPE_GRAY      ) &&
        (iColortype       != MNG_COLORTYPE_GRAYA     ) &&
        (iColortype       != MNG_COLORTYPE_RGB       ) &&
        (iColortype       != MNG_COLORTYPE_RGBA      )    ) ||
       ((pBuf->iColortype == MNG_COLORTYPE_GRAYA     ) &&
        (iColortype       != MNG_COLORTYPE_GRAYA     ) &&
        (iColortype       != MNG_COLORTYPE_RGBA      )    ) ||
       ((pBuf->iColortype == MNG_COLORTYPE_RGB       ) &&
        (iColortype       != MNG_COLORTYPE_RGB       ) &&
        (iColortype       != MNG_COLORTYPE_RGBA      )    ) ||
       ((pBuf->iColortype == MNG_COLORTYPE_RGBA      ) &&
        (iColortype       != MNG_COLORTYPE_RGBA      )    ) ||
#ifdef MNG_INCLUDE_JNG
       ((pBuf->iColortype == MNG_COLORTYPE_JPEGGRAY  ) &&
        (iColortype       != MNG_COLORTYPE_JPEGGRAY  ) &&
        (iColortype       != MNG_COLORTYPE_JPEGCOLOR ) &&
        (iColortype       != MNG_COLORTYPE_JPEGGRAYA ) &&
        (iColortype       != MNG_COLORTYPE_JPEGCOLORA)    ) ||
       ((pBuf->iColortype == MNG_COLORTYPE_JPEGCOLOR ) &&
        (iColortype       != MNG_COLORTYPE_JPEGCOLOR ) &&
        (iColortype       != MNG_COLORTYPE_JPEGCOLORA)    ) ||
       ((pBuf->iColortype == MNG_COLORTYPE_JPEGGRAYA ) &&
        (iColortype       != MNG_COLORTYPE_JPEGGRAYA ) &&
        (iColortype       != MNG_COLORTYPE_JPEGCOLORA)    ) ||
       ((pBuf->iColortype == MNG_COLORTYPE_JPEGCOLORA) &&
        (iColortype       != MNG_COLORTYPE_JPEGCOLORA)    ) ||
#endif
       ((pBuf->iColortype == MNG_COLORTYPE_INDEXED   ) &&
        (iColortype       != MNG_COLORTYPE_INDEXED   ) &&
        (iColortype       != MNG_COLORTYPE_RGB       ) &&
        (iColortype       != MNG_COLORTYPE_RGBA      )    )    )
    MNG_ERROR (pData, MNG_INVALIDCOLORTYPE);
