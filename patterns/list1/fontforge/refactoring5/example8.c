#ifndef _NO_LIBCAIRO
if ( gw->usecairo ) {
	/* Cairo can happily scroll the window -- except it doesn't know about*/
	/*  child windows, and so we don't get the requisit events to redraw */
	/*  areas covered by children. Rats. */
	GXDrawSendExpose(gw,rect->x,rect->y,rect->x+rect->width,rect->y+rect->height);
	GXDrawPopClip(_w,&old);
return;
	/* _GXCDraw_CopyArea(gw,gw,rect,rect->x+hor,rect->y+vert); */
    } else
#endif
	XCopyArea(gdisp->display,gw->w,gw->w,gdisp->gcstate[gw->ggc->bitmap_col].gc,
		rect->x,rect->y,	rect->width,rect->height,
		rect->x+hor,rect->y+vert);
