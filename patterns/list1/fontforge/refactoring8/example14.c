static void GXDrawGrabSelection(GWindow w,enum selnames sel) {
    GXDisplay *gd = (GXDisplay *) (w->display);
    GXWindow gw = (GXWindow) w;
    if ( gd->selinfo[sel].owner!=NULL && gd->selinfo[sel].datalist != NULL) {
	GEvent e;
	memset(&e,0,sizeof(e));
	e.type = et_selclear;
	e.u.selclear.sel = sel;
	e.native_window = (void *) (intpt) gd->selinfo[sel].owner->w;
	if ( gd->selinfo[sel].owner->eh!=NULL )
	    (gd->selinfo[sel].owner->eh)((GWindow) gd->selinfo[sel].owner, &e);
    }
    //Only one clipboard exists on Windows. Selectively set the selection owner
    //as otherwise the Windows clipboard will be cleared.
#ifdef _WIN32
    if (sel == sn_clipboard)
#endif
    XSetSelectionOwner(gd->display,gd->selinfo[sel].sel_atom,gw->w,gd->last_event_time);
    GXDrawClearSelData(gd,sel);
    gd->selinfo[sel].owner = gw;
    gd->selinfo[sel].timestamp = gd->last_event_time;
}
