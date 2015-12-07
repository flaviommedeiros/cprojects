switch (iStyle)                      /* alpha-modes not supported */
  {
#ifndef MNG_SKIPCANVAS_RGB8
    case MNG_CANVAS_RGB8    : break;
#endif
#ifndef MNG_SKIPCANVAS_BGR8
    case MNG_CANVAS_BGR8    : break;
#endif
#ifndef MNG_SKIPCANVAS_BGRX8
    case MNG_CANVAS_BGRX8   : break;
#endif
#ifndef MNG_SKIPCANVAS_RGB565
    case MNG_CANVAS_RGB565  : break;
#endif
#ifndef MNG_SKIPCANVAS_BGR565
    case MNG_CANVAS_BGR565  : break;
#endif
/*    case MNG_CANVAS_RGB16   : break; */
/*    case MNG_CANVAS_BGR16   : break; */
/*    case MNG_CANVAS_INDEX8  : break; */
/*    case MNG_CANVAS_GRAY8   : break; */
/*    case MNG_CANVAS_GRAY16  : break; */
/*    case MNG_CANVAS_DX15    : break; */
/*    case MNG_CANVAS_DX16    : break; */
    default                 : MNG_ERROR (((mng_datap)hHandle), MNG_INVALIDCNVSTYLE);
  }
