#ifdef HAVE_VALLOC
if (align > sizeof(long long))
		*p = valloc(size);
	else
#endif
		*p = malloc(size);
