#ifdef SINGLE_ROWBUF_ALLOC
if ((fpin = CreateFile(path, GENERIC_READ, 0, NULL, OPEN_EXISTING,
       0, NULL)) == INVALID_HANDLE_VALUE)
#else
   if ((fpin = fopen(inname, "rb")) == NULL)
#endif
   {
      fprintf(STDERR, "Could not find file %s\n", inname);
      return (1);
   }
