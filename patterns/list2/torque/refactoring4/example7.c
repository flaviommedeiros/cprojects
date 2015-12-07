#if defined(HAVE_STRUCT_STAT64) && defined(HAVE_STAT64) && defined(LARGEFILE_WORKS)
if (stat64(destdir, &sb1) == 0)
#else

  if (stat(destdir, &sb1) == 0)
#endif
    {
    char *ptr1;
    char filename[MAXPATHLEN+1];
    int complen = 0;

    /* Make sure the destination is a directory */

    if (!S_ISDIR(sb1.st_mode))
      {
      /* destination is not a directory */
      return(0);
      }

    snprintf(filename, sizeof(filename), "%s", file);

    /* Does directory match the files path? */

    ptr1 = strrchr(filename, '/');
    if (ptr1 != NULL)
      {
      ptr1[0] = '\0';

      complen = strlen(destdir);
      if (destdir[complen - 1] == '/')
        {
        /* don't include trailing slash (if any) in comparision */
        complen--;
        }

      if (memcmp(filename, destdir, complen) == 0)
        {
        /* file is going to directory*/
        return(1);
        }
      }
    }
  else if (errno == 2)
    {
    /*
     * This is okay. Probably a file that does not yet exist because
     * we have not copied it yet
     */
    }
  else
    {
    sprintf(log_buffer, "File %s stat failed, errno = %d",
            destdir,
            errno);
    log_err(-1, __func__, log_buffer);
    }
