#ifndef STDC_HEADERS
if(!getwd(cwd))
#else
  if(!getcwd(cwd, maxlen))
#endif
  {
    ctl->cmsg(CMSG_WARNING, VERB_NORMAL,
	      "Warning: Can't get current working directory");
    strcpy(cwd, ".");
  }
