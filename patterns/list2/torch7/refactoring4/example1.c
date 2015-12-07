#ifdef _WIN32
if(fseek(dfself->handle, (long)position, SEEK_SET) < 0)
#else
  THArgCheck(position <= (size_t)LLONG_MAX, 2, "position must be smaller than LLONG_MAX");
