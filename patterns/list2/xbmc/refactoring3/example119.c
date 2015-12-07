switch (pData->ePng_imgtype)
    {
#ifndef MNG_NO_1_2_4BIT_SUPPORT
    case png_g1:
      pData->fProcessrow = (mng_fptr)mng_process_g1;
      break;
    case png_g2:
      pData->fProcessrow = (mng_fptr)mng_process_g2;
      break;
    case png_g4:
      pData->fProcessrow = (mng_fptr)mng_process_g4;
      break;
#endif /* MNG_NO_1_2_4BIT_SUPPORT */
    case png_g8:
      pData->fProcessrow = (mng_fptr)mng_process_g8;
      break;
#ifndef MNG_NO_1_2_4BIT_SUPPORT
    case png_idx1:
      pData->fProcessrow = (mng_fptr)mng_process_idx1;
      break;
    case png_idx2:
      pData->fProcessrow = (mng_fptr)mng_process_idx2;
      break;
    case png_idx4:
      pData->fProcessrow = (mng_fptr)mng_process_idx4;
      break;
#endif /* MNG_NO_1_2_4BIT_SUPPORT */
    case png_idx8:
      pData->fProcessrow = (mng_fptr)mng_process_idx8;
      break;
    case png_ga8:
      pData->fProcessrow = (mng_fptr)mng_process_ga8;
      break;
    case png_rgb8:
      pData->fProcessrow = (mng_fptr)mng_process_rgb8;
      break;
    case png_rgba8:
      pData->fProcessrow = (mng_fptr)mng_process_rgba8;
      break;
#ifndef MNG_NO_16BIT_SUPPORT
    case png_g16:
      pData->fProcessrow = (mng_fptr)mng_process_g16;
      break;
    case png_ga16:
      pData->fProcessrow = (mng_fptr)mng_process_ga16;
      break;
    case png_rgb16:
      pData->fProcessrow = (mng_fptr)mng_process_rgb16;
      break;
    case png_rgba16:
      pData->fProcessrow = (mng_fptr)mng_process_rgba16;
      break;
#endif
    default:
      break;
    }
