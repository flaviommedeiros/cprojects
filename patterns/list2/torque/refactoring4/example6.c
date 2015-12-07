#if defined(HAVE_STRUCT_STAT64) && defined(HAVE_STAT64) && defined(LARGEFILE_WORKS)
if ((stat64(file1, &sb1) == 0) && (stat64(file2, &sb2) == 0))
#else
  if ((stat(file1, &sb1) == 0) && (stat(file2, &sb2) == 0))
#endif
    {

    if (!memcmp(&sb1.st_dev, &sb2.st_dev, sizeof(dev_t)) &&
    !memcmp(&sb1.st_ino, &sb2.st_ino, sizeof(ino_t)))
      {
      /* files are same */

      return(1);
      }
    }
