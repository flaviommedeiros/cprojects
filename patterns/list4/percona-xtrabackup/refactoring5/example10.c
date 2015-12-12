#ifdef FN_DEVCHAR
if ((start=strrchr(to,FN_DEVCHAR)) != 0)	/* Skip device part */
    start++;
  else
#endif
    start=to;
