#ifndef _NO_LIBCAIRO
if ( gxw->usecairo )
	_GXCDraw_Clear(gxw,rect);
    else
#endif
    {
	GXDisplay *display = (GXDisplay *) (gw->display);

	if ( rect==NULL )
	    XClearWindow(display->display,gxw->w);
	else
	    XClearArea(display->display,gxw->w,
		    rect->x,rect->y,rect->width,rect->height, false );
    }
