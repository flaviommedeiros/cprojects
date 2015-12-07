while (!(IS_DIR_SEPARATOR (*name) && p <= name + 1)	/* "/" */
#ifdef HAVE_DOS_BASED_FILE_SYSTEM
      /* On MS-DOS and MS-Windows, h:\ is different from h: */
	     && !(p == name + 3 && name[1] == ':')		/* "d:/" */
#endif
	     && IS_DIR_SEPARATOR (p[-1]))
	/* Sigh. "foo/" => "foo" */
	--p;
