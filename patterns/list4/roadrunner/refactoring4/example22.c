#if defined(_WIN32_WCE)
if ((fpout = CreateFile(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL)) == INVALID_HANDLE_VALUE)
#else
   if ((fpout = fopen(outname, "rb")) == NULL)
#endif
   {
      fprintf(STDERR, "Could not find file %s\n", outname);
      FCLOSE(fpin);
      return (1);
   }
