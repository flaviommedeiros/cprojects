#ifdef _WIN32
if (fd == -2) {
      len = wcstombs(NULL, (const wchar_t*)path, 0);
      if (len == (size_t)-1)
         len = 0;
   }
   else
#endif
      len = strlen((const char *)path);
