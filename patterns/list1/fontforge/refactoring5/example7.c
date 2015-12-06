#ifndef _NO_LIBCAIRO
if ( gxw->usecairo ) {
	_GXCDraw_FillPoly( gxw,pts,cnt);
    } else
#endif
    {
	GXDrawSetline(display,gxw->ggc);		/* Polygons draw their borders too! so we need the line mode */
	GXDrawSetcolfunc(display,gxw->ggc);	
	XFillPolygon(display->display,gxw->w,display->gcstate[gxw->ggc->bitmap_col].gc,(XPoint *) pts,cnt,Complex,CoordModeOrigin);
	XDrawLines(display->display,gxw->w,display->gcstate[gxw->ggc->bitmap_col].gc,(XPoint *) pts,cnt,CoordModeOrigin);
    }
