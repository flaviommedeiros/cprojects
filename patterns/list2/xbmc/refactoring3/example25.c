switch (iStyle)
  {
#ifndef MNG_SKIPCANVAS_RGB8
    case MNG_CANVAS_RGB8    : break;
#endif
#ifndef MNG_SKIPCANVAS_RGBA8
    case MNG_CANVAS_RGBA8   : break;
#endif
#ifndef MNG_SKIPCANVAS_RGBA8_PM
    case MNG_CANVAS_RGBA8_PM: break;
#endif
#ifndef MNG_SKIPCANVAS_ARGB8
    case MNG_CANVAS_ARGB8   : break;
#endif
#ifndef MNG_SKIPCANVAS_ARGB8_PM
    case MNG_CANVAS_ARGB8_PM: break;
#endif
#ifndef MNG_SKIPCANVAS_RGB8_A8
    case MNG_CANVAS_RGB8_A8 : break;
#endif
#ifndef MNG_SKIPCANVAS_BGR8
    case MNG_CANVAS_BGR8    : break;
#endif
#ifndef MNG_SKIPCANVAS_BGRX8
    case MNG_CANVAS_BGRX8   : break;
#endif
#ifndef MNG_SKIPCANVAS_BGRA8
    case MNG_CANVAS_BGRA8   : break;
#endif
#ifndef MNG_SKIPCANVAS_BGRA8_PM
    case MNG_CANVAS_BGRA8_PM: break;
#endif
#ifndef MNG_SKIPCANVAS_ABGR8
    case MNG_CANVAS_ABGR8   : break;
#endif
#ifndef MNG_SKIPCANVAS_ABGR8_PM
    case MNG_CANVAS_ABGR8_PM: break;
#endif
#ifndef MNG_SKIPCANVAS_RGB565
    case MNG_CANVAS_RGB565  : break;
#endif
#ifndef MNG_SKIPCANVAS_RGBA565
    case MNG_CANVAS_RGBA565 : break;
#endif
#ifndef MNG_SKIPCANVAS_BGR565
    case MNG_CANVAS_BGR565  : break;
#endif
#ifndef MNG_SKIPCANVAS_BGRA565
    case MNG_CANVAS_BGRA565 : break;
#endif
#ifndef MNG_SKIPCANVAS_BGR565_A8
    case MNG_CANVAS_BGR565_A8 : break;
#endif
#ifndef MNG_SKIPCANVAS_RGB555
    case MNG_CANVAS_RGB555  : break;
#endif
#ifndef MNG_SKIPCANVAS_BGR555
    case MNG_CANVAS_BGR555  : break;
#endif
/*    case MNG_CANVAS_RGB16   : break; */
/*    case MNG_CANVAS_RGBA16  : break; */
/*    case MNG_CANVAS_ARGB16  : break; */
/*    case MNG_CANVAS_BGR16   : break; */
/*    case MNG_CANVAS_BGRA16  : break; */
/*    case MNG_CANVAS_ABGR16  : break; */
/*    case MNG_CANVAS_INDEX8  : break; */
/*    case MNG_CANVAS_INDEXA8 : break; */
/*    case MNG_CANVAS_AINDEX8 : break; */
/*    case MNG_CANVAS_GRAY8   : break; */
/*    case MNG_CANVAS_GRAY16  : break; */
/*    case MNG_CANVAS_GRAYA8  : break; */
/*    case MNG_CANVAS_GRAYA16 : break; */
/*    case MNG_CANVAS_AGRAY8  : break; */
/*    case MNG_CANVAS_AGRAY16 : break; */
/*    case MNG_CANVAS_DX15    : break; */
/*    case MNG_CANVAS_DX16    : break; */
    default                 : { MNG_ERROR (((mng_datap)hHandle), MNG_INVALIDCNVSTYLE) };
  }
