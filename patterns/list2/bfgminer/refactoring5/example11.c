#ifdef USE_UNICODE
if (use_unicode)
		mvwhline_set(win, y, 0, WACS_HLINE, maxx);
	else
#endif
		mvwhline(win, y, 0, '-', maxx);
