#ifndef MNG_NO_1_2_4BIT_SUPPORT
if ((pData->iColortype != MNG_COLORTYPE_GRAY   ) &&
      (pData->iColortype != MNG_COLORTYPE_RGB    ) &&
      (pData->iColortype != MNG_COLORTYPE_INDEXED) &&
      (pData->iColortype != MNG_COLORTYPE_GRAYA  ) &&
      (pData->iColortype != MNG_COLORTYPE_RGBA   )    )
    MNG_ERROR (pData, MNG_INVALIDCOLORTYPE);
