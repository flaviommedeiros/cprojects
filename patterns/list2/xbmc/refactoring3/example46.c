switch (pData->iCanvasstyle)         /* determine display routine */
    {
#ifndef MNG_SKIPCANVAS_RGB8
      case MNG_CANVAS_RGB8    : { pData->fDisplayrow = (mng_fptr)mng_display_rgb8;     break; }
#endif
#ifndef MNG_SKIPCANVAS_RGBA8
      case MNG_CANVAS_RGBA8   : { pData->fDisplayrow = (mng_fptr)mng_display_rgba8;    break; }
#endif
#ifndef MNG_SKIPCANVAS_RGBA8_PM
      case MNG_CANVAS_RGBA8_PM: { pData->fDisplayrow = (mng_fptr)mng_display_rgba8_pm; break; }
#endif
#ifndef MNG_SKIPCANVAS_ARGB8
      case MNG_CANVAS_ARGB8   : { pData->fDisplayrow = (mng_fptr)mng_display_argb8;    break; }
#endif
#ifndef MNG_SKIPCANVAS_ARGB8_PM
      case MNG_CANVAS_ARGB8_PM: { pData->fDisplayrow = (mng_fptr)mng_display_argb8_pm; break; }
#endif
#ifndef MNG_SKIPCANVAS_RGB8_A8
      case MNG_CANVAS_RGB8_A8 : { pData->fDisplayrow = (mng_fptr)mng_display_rgb8_a8;  break; }
#endif
#ifndef MNG_SKIPCANVAS_BGR8
      case MNG_CANVAS_BGR8    : { pData->fDisplayrow = (mng_fptr)mng_display_bgr8;     break; }
#endif
#ifndef MNG_SKIPCANVAS_BGRX8
      case MNG_CANVAS_BGRX8   : { pData->fDisplayrow = (mng_fptr)mng_display_bgrx8;    break; }
#endif
#ifndef MNG_SKIPCANVAS_BGRA8
      case MNG_CANVAS_BGRA8   : { pData->fDisplayrow = (mng_fptr)mng_display_bgra8;    break; }
#endif
#ifndef MNG_SKIPCANVAS_BGRA8_PM
      case MNG_CANVAS_BGRA8_PM: { pData->fDisplayrow = (mng_fptr)mng_display_bgra8_pm; break; }
#endif
#ifndef MNG_SKIPCANVAS_ABGR8
      case MNG_CANVAS_ABGR8   : { pData->fDisplayrow = (mng_fptr)mng_display_abgr8;    break; }
#endif
#ifndef MNG_SKIPCANVAS_ABGR8_PM
      case MNG_CANVAS_ABGR8_PM: { pData->fDisplayrow = (mng_fptr)mng_display_abgr8_pm; break; }
#endif
#ifndef MNG_SKIPCANVAS_RGB565
      case MNG_CANVAS_RGB565  : { pData->fDisplayrow = (mng_fptr)mng_display_rgb565;   break; }
#endif
#ifndef MNG_SKIPCANVAS_RGBA565
      case MNG_CANVAS_RGBA565 : { pData->fDisplayrow = (mng_fptr)mng_display_rgba565;  break; }
#endif
#ifndef MNG_SKIPCANVAS_BGR565
      case MNG_CANVAS_BGR565  : { pData->fDisplayrow = (mng_fptr)mng_display_bgr565;   break; }
#endif
#ifndef MNG_SKIPCANVAS_BGRA565
      case MNG_CANVAS_BGRA565 : { pData->fDisplayrow = (mng_fptr)mng_display_bgra565;  break; }
#endif
#ifndef MNG_SKIPCANVAS_BGR565_A8
      case MNG_CANVAS_BGR565_A8 : { pData->fDisplayrow = (mng_fptr)mng_display_bgr565_a8;  break; }
#endif
#ifndef MNG_SKIPCANVAS_RGB555
      case MNG_CANVAS_RGB555  : { pData->fDisplayrow = (mng_fptr)mng_display_rgb555;  break; }
#endif
#ifndef MNG_SKIPCANVAS_BGR555
      case MNG_CANVAS_BGR555  : { pData->fDisplayrow = (mng_fptr)mng_display_bgr555;  break; }
#endif

#ifndef MNG_NO_16BIT_SUPPORT
/*      case MNG_CANVAS_RGB16   : { pData->fDisplayrow = (mng_fptr)mng_display_rgb16;    break; } */
/*      case MNG_CANVAS_RGBA16  : { pData->fDisplayrow = (mng_fptr)mng_display_rgba16;   break; } */
/*      case MNG_CANVAS_ARGB16  : { pData->fDisplayrow = (mng_fptr)mng_display_argb16;   break; } */
/*      case MNG_CANVAS_BGR16   : { pData->fDisplayrow = (mng_fptr)mng_display_bgr16;    break; } */
/*      case MNG_CANVAS_BGRA16  : { pData->fDisplayrow = (mng_fptr)mng_display_bgra16;   break; } */
/*      case MNG_CANVAS_ABGR16  : { pData->fDisplayrow = (mng_fptr)mng_display_abgr16;   break; } */
#endif
/*      case MNG_CANVAS_INDEX8  : { pData->fDisplayrow = (mng_fptr)mng_display_index8;   break; } */
/*      case MNG_CANVAS_INDEXA8 : { pData->fDisplayrow = (mng_fptr)mng_display_indexa8;  break; } */
/*      case MNG_CANVAS_AINDEX8 : { pData->fDisplayrow = (mng_fptr)mng_display_aindex8;  break; } */
/*      case MNG_CANVAS_GRAY8   : { pData->fDisplayrow = (mng_fptr)mng_display_gray8;    break; } */
/*      case MNG_CANVAS_AGRAY8  : { pData->fDisplayrow = (mng_fptr)mng_display_agray8;   break; } */
/*      case MNG_CANVAS_GRAYA8  : { pData->fDisplayrow = (mng_fptr)mng_display_graya8;   break; } */
#ifndef MNG_NO_16BIT_SUPPORT
/*      case MNG_CANVAS_GRAY16  : { pData->fDisplayrow = (mng_fptr)mng_display_gray16;   break; } */
/*      case MNG_CANVAS_GRAYA16 : { pData->fDisplayrow = (mng_fptr)mng_display_graya16;  break; } */
/*      case MNG_CANVAS_AGRAY16 : { pData->fDisplayrow = (mng_fptr)mng_display_agray16;  break; } */
#endif
/*      case MNG_CANVAS_DX15    : { pData->fDisplayrow = (mng_fptr)mng_display_dx15;     break; } */
/*      case MNG_CANVAS_DX16    : { pData->fDisplayrow = (mng_fptr)mng_display_dx16;     break; } */
    }
