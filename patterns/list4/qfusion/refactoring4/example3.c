#ifdef WITH_UTF8
if( !RegisterClassW( &wc ) )
#else
	wc.lpszClassName = (LPCSTR)glw_state.windowClassName;
