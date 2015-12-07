#if defined(SWIG_PYTHON_SAFE_CSTRINGS)
if (*alloc != SWIG_OLDOBJ) 
#else
	if (*alloc == SWIG_NEWOBJ) 
#endif
	  {
	    *cptr = (char *)memcpy((char *)malloc((len + 1)*sizeof(char)), cstr, sizeof(char)*(len + 1));
	    *alloc = SWIG_NEWOBJ;
	  }
	else {
	  *cptr = cstr;
	  *alloc = SWIG_OLDOBJ;
	}
