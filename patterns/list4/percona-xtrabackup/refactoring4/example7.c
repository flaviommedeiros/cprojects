#if  defined(__WIN__)
if (mkdir((char*) dir))
#else
  if (mkdir((char*) dir, Flags & my_umask_dir))
#endif
  {
    my_errno=errno;
    DBUG_PRINT("error",("error %d when creating direcory %s",my_errno,dir));
    if (MyFlags & (MY_FFNF | MY_FAE | MY_WME))
    {
      char errbuf[MYSYS_STRERROR_SIZE];
      my_error(EE_CANT_MKDIR,  MYF(ME_BELL+ME_WAITTANG), dir,
               my_errno, my_strerror(errbuf, sizeof(errbuf), my_errno));
    }
    DBUG_RETURN(-1);
  }
