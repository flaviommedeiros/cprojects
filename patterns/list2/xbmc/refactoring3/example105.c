switch (pData->iJHDRalphabitdepth)
        {
#ifndef MNG_OPTIMIZE_FOOTPRINT_INIT
#ifndef MNG_NO_1_2_4BIT_SUPPORT
          case  1 : { pData->fInitrowproc = (mng_fptr)mng_init_jpeg_a1_ni;  break; }
          case  2 : { pData->fInitrowproc = (mng_fptr)mng_init_jpeg_a2_ni;  break; }
          case  4 : { pData->fInitrowproc = (mng_fptr)mng_init_jpeg_a4_ni;  break; }
#endif /* MNG_NO_1_2_4BIT_SUPPORT */
          case  8 : { pData->fInitrowproc = (mng_fptr)mng_init_jpeg_a8_ni;  break; }
#ifndef MNG_NO_16BIT_SUPPORT
          case 16 : { pData->fInitrowproc = (mng_fptr)mng_init_jpeg_a16_ni; break; }
#endif
#else
#ifndef MNG_NO_1_2_4BIT_SUPPORT
          case  1 : { pData->ePng_imgtype = png_jpeg_a1;  break; }
          case  2 : { pData->ePng_imgtype = png_jpeg_a2;  break; }
          case  4 : { pData->ePng_imgtype = png_jpeg_a4;  break; }
#endif /* MNG_NO_1_2_4BIT_SUPPORT */
          case  8 : { pData->ePng_imgtype = png_jpeg_a8;  break; }
#ifndef MNG_NO_16BIT_SUPPORT
          case 16 : { pData->ePng_imgtype = png_jpeg_a16; break; }
#endif
#endif
        }
