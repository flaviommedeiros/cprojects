if ((my_flags & MY_IGNORE_BADFD) &&
        (er == EBADF || er == EINVAL || er == EROFS
#ifdef __APPLE__
        || er == ENOTSUP
#endif
        ))
    {
      DBUG_PRINT("info", ("ignoring errno %d", er));
      res= 0;
    }
    else if (my_flags & MY_WME)
    {
      char errbuf[MYSYS_STRERROR_SIZE];
      my_error(EE_SYNC, MYF(ME_BELL+ME_WAITTANG), my_filename(fd),
               my_errno, my_strerror(errbuf, sizeof(errbuf), my_errno));
    }
