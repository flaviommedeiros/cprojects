switch (pData->ePng_imgtype)
    {
#ifndef MNG_NO_1_2_4BIT_SUPPORT
    case png_g1:
      pData->fStorerow = (mng_fptr)mng_store_g1;
      break;
    case png_g2:
      pData->fStorerow = (mng_fptr)mng_store_g2;
      break;
    case png_g4:
      pData->fStorerow = (mng_fptr)mng_store_g4;
      break;
#endif /* MNG_NO_1_2_4BIT_SUPPORT */
    case png_g8:
      pData->fStorerow = (mng_fptr)mng_store_g8;
      break;
#ifndef MNG_NO_1_2_4BIT_SUPPORT
    case png_idx1:
      pData->fStorerow = (mng_fptr)mng_store_idx1;
      break;
    case png_idx2:
      pData->fStorerow = (mng_fptr)mng_store_idx2;
      break;
    case png_idx4:
      pData->fStorerow = (mng_fptr)mng_store_idx4;
      break;
#endif /* MNG_NO_1_2_4BIT_SUPPORT */
    case png_idx8:
      pData->fStorerow = (mng_fptr)mng_store_idx8;
      break;
    case png_ga8:
      pData->fStorerow = (mng_fptr)mng_store_ga8;
      break;
    case png_rgb8:
      pData->fStorerow = (mng_fptr)mng_store_rgb8;
      break;
    case png_rgba8:
      pData->fStorerow = (mng_fptr)mng_store_rgba8;
      break;
#ifndef MNG_NO_16BIT_SUPPORT
    case png_g16:
      pData->fStorerow = (mng_fptr)mng_store_g16;
      break;
    case png_ga16:
      pData->fStorerow = (mng_fptr)mng_store_ga16;
      break;
    case png_rgb16:
      pData->fStorerow = (mng_fptr)mng_store_rgb16;
      break;
    case png_rgba16:
      pData->fStorerow = (mng_fptr)mng_store_rgba16;
      break;
#endif

#ifdef MNG_INCLUDE_JNG
#ifndef MNG_NO_1_2_4BIT_SUPPORT
    case png_jpeg_a1:
/*  if (pData->iJHDRimgbitdepth == 8) */
      {
        switch (pData->iJHDRcolortype)
        {
        case 12 :
          { pData->fStorerow = (mng_fptr)mng_store_jpeg_g8_a1;   break; }
        case 14 :
          { pData->fStorerow = (mng_fptr)mng_store_jpeg_rgb8_a1; break; }
        }
      }
      /* TODO: bitdepth 12 & 20 */
      break;
    case png_jpeg_a2:
/*  if (pData->iJHDRimgbitdepth == 8) */
      {
        switch (pData->iJHDRcolortype)
        {
          case 12 :
            { pData->fStorerow = (mng_fptr)mng_store_jpeg_g8_a2;   break; }
          case 14 :
            { pData->fStorerow = (mng_fptr)mng_store_jpeg_rgb8_a2; break; }
        }
      }
      break;
      /* TODO: bitdepth 12 & 20 */
    case png_jpeg_a4:
/*  if (pData->iJHDRimgbitdepth == 8) */
      {
        switch (pData->iJHDRcolortype)
        {
          case 12 :
           { pData->fStorerow = (mng_fptr)mng_store_jpeg_g8_a4;   break; }
          case 14 :
           { pData->fStorerow = (mng_fptr)mng_store_jpeg_rgb8_a4; break; }
        }
      }
      break;
#endif /* MNG_NO_1_2_4BIT_SUPPORT */
      /* TODO: bitdepth 12 & 20 */
    case png_jpeg_a8:
/*  if (pData->iJHDRimgbitdepth == 8) */
      {
        switch (pData->iJHDRcolortype)
        {
          case 12 :
            { pData->fStorerow = (mng_fptr)mng_store_jpeg_g8_a8;   break; }
          case 14 :
            { pData->fStorerow = (mng_fptr)mng_store_jpeg_rgb8_a8; break; }
        }
      }
      break;
      /* TODO: bitdepth 12 & 20 */
#ifndef MNG_NO_16BIT_SUPPORT
    case png_jpeg_a16:
/*  if (pData->iJHDRimgbitdepth == 8) */
      {
        switch (pData->iJHDRcolortype)
        {
          case 12 :
            { pData->fStorerow = (mng_fptr)mng_store_jpeg_g8_a16;   break; }
          case 14 :
            { pData->fStorerow = (mng_fptr)mng_store_jpeg_rgb8_a16; break; }
        }
      }
      break;
      /* TODO: bitdepth 12 & 20 */
#endif
#endif /* MNG_INCLUDE_JNG */
    default:
      break;
    }
