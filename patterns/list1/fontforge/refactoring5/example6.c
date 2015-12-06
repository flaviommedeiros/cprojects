#ifndef _NO_LIBCAIRO
if ( gxw->usecairo ) {
	_GXCDraw_DrawPoly( gxw,pts,cnt);
    } else
#endif
    {
	GXDrawSetline(display,gxw->ggc);
	XDrawLines(display->display,gxw->w,display->gcstate[gxw->ggc->bitmap_col].gc,(XPoint *) pts,cnt,CoordModeOrigin);
    }
