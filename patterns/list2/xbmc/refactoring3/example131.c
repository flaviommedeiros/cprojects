switch (pData->ePng_imgtype)
  {
#ifndef MNG_NO_1_2_4BIT_SUPPORT
    case png_g1:
#ifdef MNG_INCLUDE_JNG
    case png_jpeg_a1:
#endif
      pData->fDifferrow  = (mng_fptr)mng_differ_g1;
      break;
    case png_g2:
#ifdef MNG_INCLUDE_JNG
    case png_jpeg_a2:
#endif
      pData->fDifferrow  = (mng_fptr)mng_differ_g2;
      break;
    case png_g4:
#ifdef MNG_INCLUDE_JNG
    case png_jpeg_a4:
#endif
      pData->fDifferrow  = (mng_fptr)mng_differ_g4;
      break;
#endif /* MNG_NO_1_2_4BIT_SUPPORT */
    case png_g8:
#ifdef MNG_INCLUDE_JNG
    case png_jpeg_a8:
#endif
      pData->fDifferrow  = (mng_fptr)mng_differ_g8;
      break;
    case png_rgb8:
      pData->fDifferrow  = (mng_fptr)mng_differ_rgb8;
      break;
#ifndef MNG_NO_1_2_4BIT_SUPPORT
    case png_idx1:
      pData->fDifferrow  = (mng_fptr)mng_differ_idx1;
      break;
    case png_idx2:
      pData->fDifferrow  = (mng_fptr)mng_differ_idx2;
      break;
    case png_idx4:
      pData->fDifferrow  = (mng_fptr)mng_differ_idx4;
      break;
#endif /* MNG_NO_1_2_4BIT_SUPPORT */
    case png_idx8:
      pData->fDifferrow  = (mng_fptr)mng_differ_idx8;
      break;
    case png_ga8:
      pData->fDifferrow  = (mng_fptr)mng_differ_ga8;
      break;
    case png_rgb8:
      pData->fDifferrow  = (mng_fptr)mng_differ_rgb8;
      break;
    case png_rgba8:
      pData->fDifferrow  = (mng_fptr)mng_differ_rgba8;
      break;
#ifndef MNG_NO_16BIT_SUPPORT
    case png_g16:
#ifdef MNG_INCLUDE_JNG
    case png_jpeg_a16:
#endif
      pData->fDifferrow  = (mng_fptr)mng_differ_g16;
      break;
    case png_ga16:
      pData->fDifferrow  = (mng_fptr)mng_differ_ga16;
      break;
    case png_rgb16:
      pData->fDifferrow  = (mng_fptr)mng_differ_rgb16;
      break;
    case png_rgba16:
      pData->fDifferrow  = (mng_fptr)mng_differ_rgba16;
      break;
#endif
    default:
      break;
  }
