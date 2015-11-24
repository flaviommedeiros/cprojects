#ifndef _NO_LIBCAIRO
if ( gxw->usecairo ) {
	_GXCDraw_FillEllipse( gxw,rect);
    } else
#endif
    {
	GXDrawSetcolfunc(display,gxw->ggc);
	XFillArc(display->display,gxw->w,display->gcstate[gxw->ggc->bitmap_col].gc,rect->x,rect->y,
		rect->width,rect->height,0,360*64);
    }
