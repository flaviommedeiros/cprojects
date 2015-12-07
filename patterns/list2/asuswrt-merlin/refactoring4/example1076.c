#if OS_VXWORKS
if( fsync(fd)==-1 )
#else
      if( fsync(fd) )
#endif
      {
        rc = SQLITE_IOERR_DIR_FSYNC;
      }
