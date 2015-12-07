if( errno==ENOENT
#if OS_VXWORKS
        || osAccess(zPath,0)!=0
#endif
    ){
      rc = SQLITE_IOERR_DELETE_NOENT;
    }else{
      rc = unixLogError(SQLITE_IOERR_DELETE, "unlink", zPath);
    }
