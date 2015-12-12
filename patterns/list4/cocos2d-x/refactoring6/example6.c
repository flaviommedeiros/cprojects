if (!strchr(name, '/')
#ifdef __CYGWIN__
      && !strchr(name, '\\')
#endif
     ) {
    if (!strchr(name, '.')) {
      name = lj_str_pushf(L, CLIB_SOEXT, name);
      L->top--;
#ifdef __CYGWIN__
    } else {
      return name;
#endif
    }
    if (!(name[0] == CLIB_SOPREFIX[0] && name[1] == CLIB_SOPREFIX[1] &&
	  name[2] == CLIB_SOPREFIX[2])) {
      name = lj_str_pushf(L, CLIB_SOPREFIX "%s", name);
      L->top--;
    }
  }
