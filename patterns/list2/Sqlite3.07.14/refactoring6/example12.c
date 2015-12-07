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
      //å¦æä¸ä¸ªéè¯¯åçå¨findInodeInfo()ï¼ç«å³å³é­æä»¶æè¿°ç¬¦ï¼ä¹åéæ¾äºæ¥éã
      //findInodeInfo()å°å¨ä¸¤ä¸ªæå¢ä¸å¤±è´¥
      //      (a)å¯¹fstat()çè°ç¨å¤±è´¥
      //      (b)ä¸ä¸ªåå­åéå¤±è´¥
      **
      ** Scenario (b) may only occur if the process is holding no other
      ** file descriptors open on the same file. If there were other file
      ** descriptors on this file, then no malloc would be required by
      ** findInodeInfo(). If this is the case, it is quite safe to close
      ** handle h - as it is guaranteed that no posix locks will be released
      ** by doing so.
      **
      //ææ¯(b)å¯è½åªåçå¨å¦æç¸åæä»¶ä¸­æ­¤è¿ç¨æ²¡æä¿æå¶ä»æä»¶æè¿°ç¬¦çæåµã
      //å¦ææ²¡æå¶ä»æä»¶æè¿°ç¬¦å¨è¿ä¸ªæä»¶ä¸­ï¼åfindInodeInfo()ä¸ä¼è¢«è¦æ±åéã
      //å¦æå¨è¿ç§æåµä¸ï¼ä»æ¯éå¸¸å®å¨çå»å³é­hå¥æ-å¦æè¿ä¹å
      //å®ä¼è¢«ä¿è¯éå¯ç§»æ¤æ§æä½ç³»ç»æ¥å£éå°ä¼è¢«éæ¾
      ** If scenario (a) caused the error then things are not so safe. The
      ** implicit assumption here is that if fstat() fails, things are in
      ** such bad shape that dropping a lock or two doesn't matter much.
      */
      //å¦æææ¯(a)åçéè¯¯å°ä¸ä¼å¦æ­¤å®å¨ãè¿ééå«çåè®¾æ¯fstat()è°ç¨å¤±è´¥ï¼
      //å¨è¿ç§æåºä¸ä¸¤ä¸ªéçåçæ¨¡åæ å³ç´§è¦ã
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
    //AFP éå®ä½¿ç¨æä»¶è·¯å¾ï¼æä»¥å®éè¦è¢«åå«å¨afpLockingContextä¸­ã
    afpLockingContext *pCtx;
    pNew->lockingContext = pCtx = sqlite3_malloc( sizeof(*pCtx) );
    if( pCtx==0 ){
      rc = SQLITE_NOMEM;
    }else{
      /* NB: zFilename exists and remains valid until the file is closed
      ** according to requirement F11141.  So we do not need to make a
      ** copy of the filename. */
      //éæ³¨ï¼zFilenameå­å¨,ä»ç¶ææ,ç´å°æä»¶æ ¹æ®F11141è¦æ±å³é­ãæä»¥æä»¬ä¸éè¦æä»¶çå¯æ¬ã
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
    //ç¹æä»¶éå®ä½¿ç¨æä»¶è·¯å¾æä»¥å®éè¦è¢«åå«å¨dotlockLockingContext
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
    //è¢«å½åä¸ºä¿¡å·éçä½¿ç¨æä»¶è·¯å¾æä»¥å®éè¦è¢«åå«å¨semLockingContext
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
