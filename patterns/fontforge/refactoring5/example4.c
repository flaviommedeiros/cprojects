#ifndef _NO_LIBCAIRO
if ( gxw->usecairo ) {
	_GXCDraw_DrawEllipse( gxw,rect);
    } else
#endif
    {
	GXDisplay *display = gxw->display;

	GXDrawSetline(display,gxw->ggc);
	XDrawArc(display->display,gxw->w,display->gcstate[gxw->ggc->bitmap_col].gc,rect->x,rect->y,
		rect->width,rect->height,0,360*64);
    }
