if (h == NULL
#ifdef NDEBUG /* in production ignore errors for non-existent modules */
   && GetLastError() != ERROR_MOD_NOT_FOUND
#endif
      )
    vprintLastError(TEXT("LoadLibrary(%s)"), libName);
