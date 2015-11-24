#ifdef _WIN32
if (sel == sn_clipboard)
#endif
    XSetSelectionOwner(gd->display,gd->selinfo[sel].sel_atom,gw->w,gd->last_event_time);
