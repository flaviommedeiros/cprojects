static const char *azEndings[] = {
#if SQLITE_OS_WIN
     "dll"   
#elif defined(__APPLE__)
     "dylib"
#else
     "so"
#endif
  };
