#ifdef SUPPORT_LIBBZ2
if (frtype == FR_LIBBZ2)
  {
  if (rc == 3)
    {
    int errnum;
    const char *err = BZ2_bzerror(inbz2, &errnum);
    if (errnum == BZ_DATA_ERROR_MAGIC)
      {
      BZ2_bzclose(inbz2);
      goto PLAIN_FILE;
      }
    else if (!silent)
      fprintf(stderr, "pcregrep: Failed to read %s using bzlib: %s\n",
        pathname, err);
    rc = 2;    /* The normal "something went wrong" code */
    }
  BZ2_bzclose(inbz2);
  }
else
#endif

/* Normal file close */

fclose(in);
