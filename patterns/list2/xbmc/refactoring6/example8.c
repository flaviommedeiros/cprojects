if ( ((pBuf->iColortype      == MNG_COLORTYPE_GRAY      ) &&
        (pData->iPROMcolortype != MNG_COLORTYPE_GRAY      ) &&
        (pData->iPROMcolortype != MNG_COLORTYPE_GRAYA     ) &&
        (pData->iPROMcolortype != MNG_COLORTYPE_RGB       ) &&
        (pData->iPROMcolortype != MNG_COLORTYPE_RGBA      )    ) ||
       ((pBuf->iColortype      == MNG_COLORTYPE_GRAYA     ) &&
        (pData->iPROMcolortype != MNG_COLORTYPE_GRAYA     ) &&
        (pData->iPROMcolortype != MNG_COLORTYPE_RGBA      )    ) ||
       ((pBuf->iColortype      == MNG_COLORTYPE_RGB       ) &&
        (pData->iPROMcolortype != MNG_COLORTYPE_RGB       ) &&
        (pData->iPROMcolortype != MNG_COLORTYPE_RGBA      )    ) ||
       ((pBuf->iColortype      == MNG_COLORTYPE_RGBA      ) &&
        (pData->iPROMcolortype != MNG_COLORTYPE_RGBA      )    ) ||
#ifdef MNG_INCLUDE_JNG
       ((pBuf->iColortype      == MNG_COLORTYPE_JPEGGRAY  ) &&
        (pData->iPROMcolortype != MNG_COLORTYPE_JPEGGRAY  ) &&
        (pData->iPROMcolortype != MNG_COLORTYPE_JPEGCOLOR ) &&
        (pData->iPROMcolortype != MNG_COLORTYPE_JPEGGRAYA ) &&
        (pData->iPROMcolortype != MNG_COLORTYPE_JPEGCOLORA)    ) ||
       ((pBuf->iColortype      == MNG_COLORTYPE_JPEGCOLOR ) &&
        (pData->iPROMcolortype != MNG_COLORTYPE_JPEGCOLOR ) &&
        (pData->iPROMcolortype != MNG_COLORTYPE_JPEGCOLORA)    ) ||
       ((pBuf->iColortype      == MNG_COLORTYPE_JPEGGRAYA ) &&
        (pData->iPROMcolortype != MNG_COLORTYPE_JPEGGRAYA ) &&
        (pData->iPROMcolortype != MNG_COLORTYPE_JPEGCOLORA)    ) ||
       ((pBuf->iColortype      == MNG_COLORTYPE_JPEGCOLORA) &&
        (pData->iPROMcolortype != MNG_COLORTYPE_JPEGCOLORA)    ) ||
#endif
       ((pBuf->iColortype      == MNG_COLORTYPE_INDEXED   ) &&
        (pData->iPROMcolortype != MNG_COLORTYPE_INDEXED   ) &&
        (pData->iPROMcolortype != MNG_COLORTYPE_RGB       ) &&
        (pData->iPROMcolortype != MNG_COLORTYPE_RGBA      )    )    )
    MNG_ERROR (pData, MNG_INVALIDCOLORTYPE);
