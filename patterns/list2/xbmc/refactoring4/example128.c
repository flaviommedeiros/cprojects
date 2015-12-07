#ifndef __W32__
if(*p==PATH_SEP)
#else
	  if(*p=='/' || *p=='\\' || *p==':')
#endif
	    *p = '_';
