if( pLockingStyle == &posixIoMethods
#if defined(__APPLE__) && SQLITE_ENABLE_LOCKING_STYLE
    || pLockingStyle == &nfsIoMethods
#endif
  ){
    unixEnterMutex();
    rc = findInodeInfo(pNew, &pNew->pInode);
    if( rc!=SQLITE_OK ){
      /* If an error occured in findInodeInfo(), close the file descriptor
      ** immediately, before releasing the mutex. findInodeInfo() may fail
      ** in two scenarios:
      **
      **   (a) A call to fstat() failed.
      **   (b) A malloc failed.
      **
      ** Scenario (b) may only occur if the process is holding no other
      ** file descriptors open on the same file. If there were other file
      ** descriptors on this file, then no malloc would be required by
      ** findInodeInfo(). If this is the case, it is quite safe to close
      ** handle h - as it is guaranteed that no posix locks will be released
      ** by doing so.
      **
      ** If scenario (a) caused the error then things are not so safe. The
      ** implicit assumption here is that if fstat() fails, things are in
      ** such bad shape that dropping a lock or two doesn't matter much.
      */
      robust_close(pNew, h, __LINE__);
      h = -1;
    }
    unixLeaveMutex();
  }

#if SQLITE_ENABLE_LOCKING_STYLE && defined(__APPLE__)
  else if( pLockingStyle == &afpIoMethods ){
    /* AFP locking uses the file path so it needs to be included in
    ** the afpLockingContext.
    */
    afpLockingContext *pCtx;
    pNew->lockingContext = pCtx = sqlite3_malloc( sizeof(*pCtx) );
    if( pCtx==0 ){
      rc = SQLITE_NOMEM;
    }else{
      /* NB: zFilename exists and remains valid until the file is closed
      ** according to requirement F11141.  So we do not need to make a
      ** copy of the filename. */
      pCtx->dbPath = zFilename;
      pCtx->reserved = 0;
      srandomdev();
      unixEnterMutex();
      rc = findInodeInfo(pNew, &pNew->pInode);
      if( rc!=SQLITE_OK ){
        sqlite3_free(pNew->lockingContext);
        robust_close(pNew, h, __LINE__);
        h = -1;
      }
      unixLeaveMutex();        
    }
  }
#endif

  else if( pLockingStyle == &dotlockIoMethods ){
    /* Dotfile locking uses the file path so it needs to be included in
    ** the dotlockLockingContext 
    */
    char *zLockFile;
    int nFilename;
    assert( zFilename!=0 );
    nFilename = (int)strlen(zFilename) + 6;
    zLockFile = (char *)sqlite3_malloc(nFilename);
    if( zLockFile==0 ){
      rc = SQLITE_NOMEM;
    }else{
      sqlite3_snprintf(nFilename, zLockFile, "%s" DOTLOCK_SUFFIX, zFilename);
    }
    pNew->lockingContext = zLockFile;
  }

#if OS_VXWORKS
  else if( pLockingStyle == &semIoMethods ){
    /* Named semaphore locking uses the file path so it needs to be
    ** included in the semLockingContext
    */
    unixEnterMutex();
    rc = findInodeInfo(pNew, &pNew->pInode);
    if( (rc==SQLITE_OK) && (pNew->pInode->pSem==NULL) ){
      char *zSemName = pNew->pInode->aSemName;
      int n;
      sqlite3_snprintf(MAX_PATHNAME, zSemName, "/%s.sem",
                       pNew->pId->zCanonicalName);
      for( n=1; zSemName[n]; n++ )
        if( zSemName[n]=='/' ) zSemName[n] = '_';
      pNew->pInode->pSem = sem_open(zSemName, O_CREAT, 0666, 1);
      if( pNew->pInode->pSem == SEM_FAILED ){
        rc = SQLITE_NOMEM;
        pNew->pInode->aSemName[0] = '\0';
      }
    }
    unixLeaveMutex();
  }
