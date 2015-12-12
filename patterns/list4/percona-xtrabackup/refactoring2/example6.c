#if __WIN__
if (GetModuleFileName(NULL, self_name, FN_REFLEN) == 0)
#endif
  {
    strncpy(self_name, argv[0], FN_REFLEN);
  }
