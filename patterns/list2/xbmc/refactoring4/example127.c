#ifndef __W32__
if(*p == '.' || *p == '#')
#else
	if(*p == '#')
#endif
	  *p = '_';
