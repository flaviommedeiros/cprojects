# ifdef HAVE_FORK
if (fork())
# else
	if (vfork())
# endif
		return;
