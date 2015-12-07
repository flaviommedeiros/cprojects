#if defined (ENOTSUP)
if (errno == ENOTTY || errno == ENOTSUP)
#else
      if (errno == ENOTTY)
#endif
	readline_echoing_p = 1;
