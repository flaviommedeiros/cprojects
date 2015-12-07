switch (pData->ePng_imgtype)
  {
#ifndef MNG_NO_1_2_4BIT_SUPPORT
    case png_g1:
    case png_idx1:
#ifdef MNG_INCLUDE_JNG
    case png_jpeg_a1:
#endif
        pData->iSamplemul  = 1;
        pData->iSampleofs  = 7;
        pData->iSamplediv  = 3;
        pData->iFilterbpp  = 1;
        break;
    case png_g2:
    case png_idx2:
#ifdef MNG_INCLUDE_JNG
    case png_jpeg_a2:
#endif
        pData->iSamplemul  = 1;
        pData->iSampleofs  = 3;
        pData->iSamplediv  = 2;
        pData->iFilterbpp  = 1;
        break;
    case png_g4:
    case png_idx4:
#ifdef MNG_INCLUDE_JNG
    case png_jpeg_a4:
#endif
        pData->iSamplemul  = 1;
        pData->iSampleofs  = 1;
        pData->iSamplediv  = 1;
        pData->iFilterbpp  = 1;
        break;
#endif /* MNG_NO_1_2_4BIT_SUPPORT */
    case png_g8:
    case png_idx8:
#ifdef MNG_INCLUDE_JNG
    case png_jpeg_a8:
#endif
        pData->iSamplemul  = 1;
        pData->iSampleofs  = 0;
        pData->iSamplediv  = 0;
        pData->iFilterbpp  = 1;
        break;
    case png_ga8:
#ifndef MNG_NO_16BIT_SUPPORT
    case png_g16:
#ifdef MNG_INCLUDE_JNG
    case png_jpeg_a16:
#endif
#endif
        pData->iSamplemul  = 2;
        pData->iSampleofs  = 0;
        pData->iSamplediv  = 0;
        pData->iFilterbpp  = 2;
        break;
    case png_rgb8:
        pData->iSamplemul  = 3;
        pData->iSampleofs  = 0;
        pData->iSamplediv  = 0;
        pData->iFilterbpp  = 3;
        break;
#ifndef MNG_NO_16BIT_SUPPORT
    case png_ga16:
#endif
    case png_rgba8:
        pData->iSamplemul  = 4;
        pData->iSampleofs  = 0;
        pData->iSamplediv  = 0;
        pData->iFilterbpp  = 4;
        break;
#ifndef MNG_NO_16BIT_SUPPORT
    case png_rgb16:
        pData->iSamplemul  = 6;
        pData->iSampleofs  = 0;
        pData->iSamplediv  = 0;
        pData->iFilterbpp  = 6;
        break;
    case png_rgba16:
        pData->iSamplemul  = 8;
        pData->iSampleofs  = 0;
        pData->iSamplediv  = 0;
        pData->iFilterbpp  = 8;
        break;
#endif
    default:
        break;
  }
