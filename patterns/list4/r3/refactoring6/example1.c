if (
#if defined(TO_OSX) || defined(TO_OSXI)
		Try_Browser("/usr/bin/open", url)
#else
		Try_Browser("xdg-open", url)
		|| Try_Browser("x-www-browser", url)
#endif
	) return TRUE;
