switch (pData->iBkgdstyle)
        {
#ifndef MNG_SKIPCANVAS_RGB8
          case MNG_CANVAS_RGB8    : { pData->fRestbkgdrow = (mng_fptr)mng_restore_bkgd_rgb8;    break; }
#endif
#ifndef MNG_SKIPCANVAS_BGR8
          case MNG_CANVAS_BGR8    : { pData->fRestbkgdrow = (mng_fptr)mng_restore_bkgd_bgr8;    break; }
#endif
#ifndef MNG_SKIPCANVAS_BGRX8
          case MNG_CANVAS_BGRX8   : { pData->fRestbkgdrow = (mng_fptr)mng_restore_bkgd_bgrx8;   break; }
#endif
#ifndef MNG_SKIPCANVAS_BGR565
          case MNG_CANVAS_BGR565  : { pData->fRestbkgdrow = (mng_fptr)mng_restore_bkgd_bgr565;  break; }
#endif
#ifndef MNG_SKIPCANVAS_RGB565
          case MNG_CANVAS_RGB565  : { pData->fRestbkgdrow = (mng_fptr)mng_restore_bkgd_rgb565;  break; }
#endif
#ifndef MNG_NO_16BIT_SUPPORT
  /*        case MNG_CANVAS_RGB16   : { pData->fRestbkgdrow = (mng_fptr)mng_restore_bkgd_rgb16;   break; } */
  /*        case MNG_CANVAS_BGR16   : { pData->fRestbkgdrow = (mng_fptr)mng_restore_bkgd_bgr16;   break; } */
#endif
  /*        case MNG_CANVAS_INDEX8  : { pData->fRestbkgdrow = (mng_fptr)mng_restore_bkgd_index8;  break; } */
  /*        case MNG_CANVAS_GRAY8   : { pData->fRestbkgdrow = (mng_fptr)mng_restore_bkgd_gray8;   break; } */
#ifndef MNG_NO_16BIT_SUPPORT
  /*        case MNG_CANVAS_GRAY16  : { pData->fRestbkgdrow = (mng_fptr)mng_restore_bkgd_gray16;  break; } */
#endif
  /*        case MNG_CANVAS_DX15    : { pData->fRestbkgdrow = (mng_fptr)mng_restore_bkgd_dx15;    break; } */
  /*        case MNG_CANVAS_DX16    : { pData->fRestbkgdrow = (mng_fptr)mng_restore_bkgd_dx16;    break; } */
        }
