#if defined(_WIN32_WCE)
if ((fpout = CreateFile(path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL)) == INVALID_HANDLE_VALUE)
#else
   if ((fpout = fopen(outname, "wb")) == NULL)
#endif
   {
      fprintf(STDERR, "Could not open output file %s\n", outname);
      FCLOSE(fpin);
      return (1);
   }
