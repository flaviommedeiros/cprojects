switch (pData->ePng_imgtype)
    {
#ifndef MNG_NO_1_2_4BIT_SUPPORT
    case png_g1:
      pData->fStorerow = (mng_fptr)mng_delta_g1;
      break;
    case png_g2:
      pData->fStorerow = (mng_fptr)mng_delta_g2;
      break;
    case png_g4:
      pData->fStorerow = (mng_fptr)mng_delta_g4;
      break;
#endif /* MNG_NO_1_2_4BIT_SUPPORT */
    case png_g8:
      pData->fStorerow = (mng_fptr)mng_delta_g8;
      break;
#ifndef MNG_NO_1_2_4BIT_SUPPORT
    case png_idx1:
      pData->fStorerow = (mng_fptr)mng_delta_idx1;
      break;
    case png_idx2:
      pData->fStorerow = (mng_fptr)mng_delta_idx2;
      break;
    case png_idx4:
      pData->fStorerow = (mng_fptr)mng_delta_idx4;
      break;
#endif /* MNG_NO_1_2_4BIT_SUPPORT */
    case png_idx8:
      pData->fStorerow = (mng_fptr)mng_delta_idx8;
      break;
    case png_ga8:
      pData->fStorerow = (mng_fptr)mng_delta_ga8;
      break;
    case png_rgb8:
      pData->fStorerow = (mng_fptr)mng_delta_rgb8;
      break;
    case png_rgba8:
      pData->fStorerow = (mng_fptr)mng_delta_rgba8;
      break;
#ifndef MNG_NO_16BIT_SUPPORT
    case png_g16:
      pData->fStorerow = (mng_fptr)mng_delta_g16;
      break;
    case png_ga16:
      pData->fStorerow = (mng_fptr)mng_delta_ga16;
      break;
    case png_rgb16:
      pData->fStorerow = (mng_fptr)mng_delta_rgb16;
      break;
    case png_rgba16:
      pData->fStorerow = (mng_fptr)mng_delta_rgba16;
      break;
#endif
    default:
      break;
    }
