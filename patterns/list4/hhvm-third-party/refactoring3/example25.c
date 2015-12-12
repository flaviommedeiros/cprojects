switch( op ){

    /* Mutex configuration options are only available in a threadsafe
    ** compile. 
    */
#if defined(SQLITE_THREADSAFE) && SQLITE_THREADSAFE>0
    case SQLITE_CONFIG_SINGLETHREAD: {
      /* Disable all mutexing */
      sqlite3GlobalConfig.bCoreMutex = 0;
      sqlite3GlobalConfig.bFullMutex = 0;
      break;
    }
    case SQLITE_CONFIG_MULTITHREAD: {
      /* Disable mutexing of database connections */
      /* Enable mutexing of core data structures */
      sqlite3GlobalConfig.bCoreMutex = 1;
      sqlite3GlobalConfig.bFullMutex = 0;
      break;
    }
    case SQLITE_CONFIG_SERIALIZED: {
      /* Enable all mutexing */
      sqlite3GlobalConfig.bCoreMutex = 1;
      sqlite3GlobalConfig.bFullMutex = 1;
      break;
    }
    case SQLITE_CONFIG_MUTEX: {
      /* Specify an alternative mutex implementation */
      sqlite3GlobalConfig.mutex = *va_arg(ap, sqlite3_mutex_methods*);
      break;
    }
    case SQLITE_CONFIG_GETMUTEX: {
      /* Retrieve the current mutex implementation */
      *va_arg(ap, sqlite3_mutex_methods*) = sqlite3GlobalConfig.mutex;
      break;
    }
#endif


    case SQLITE_CONFIG_MALLOC: {
      /* Specify an alternative malloc implementation */
      sqlite3GlobalConfig.m = *va_arg(ap, sqlite3_mem_methods*);
      break;
    }
    case SQLITE_CONFIG_GETMALLOC: {
      /* Retrieve the current malloc() implementation */
      if( sqlite3GlobalConfig.m.xMalloc==0 ) sqlite3MemSetDefault();
      *va_arg(ap, sqlite3_mem_methods*) = sqlite3GlobalConfig.m;
      break;
    }
    case SQLITE_CONFIG_MEMSTATUS: {
      /* Enable or disable the malloc status collection */
      sqlite3GlobalConfig.bMemstat = va_arg(ap, int);
      break;
    }
    case SQLITE_CONFIG_SCRATCH: {
      /* Designate a buffer for scratch memory space */
      sqlite3GlobalConfig.pScratch = va_arg(ap, void*);
      sqlite3GlobalConfig.szScratch = va_arg(ap, int);
      sqlite3GlobalConfig.nScratch = va_arg(ap, int);
      break;
    }
    case SQLITE_CONFIG_PAGECACHE: {
      /* Designate a buffer for page cache memory space */
      sqlite3GlobalConfig.pPage = va_arg(ap, void*);
      sqlite3GlobalConfig.szPage = va_arg(ap, int);
      sqlite3GlobalConfig.nPage = va_arg(ap, int);
      break;
    }

    case SQLITE_CONFIG_PCACHE: {
      /* no-op */
      break;
    }
    case SQLITE_CONFIG_GETPCACHE: {
      /* now an error */
      rc = SQLITE_ERROR;
      break;
    }

    case SQLITE_CONFIG_PCACHE2: {
      /* Specify an alternative page cache implementation */
      sqlite3GlobalConfig.pcache2 = *va_arg(ap, sqlite3_pcache_methods2*);
      break;
    }
    case SQLITE_CONFIG_GETPCACHE2: {
      if( sqlite3GlobalConfig.pcache2.xInit==0 ){
        sqlite3PCacheSetDefault();
      }
      *va_arg(ap, sqlite3_pcache_methods2*) = sqlite3GlobalConfig.pcache2;
      break;
    }

#if defined(SQLITE_ENABLE_MEMSYS3) || defined(SQLITE_ENABLE_MEMSYS5)
    case SQLITE_CONFIG_HEAP: {
      /* Designate a buffer for heap memory space */
      sqlite3GlobalConfig.pHeap = va_arg(ap, void*);
      sqlite3GlobalConfig.nHeap = va_arg(ap, int);
      sqlite3GlobalConfig.mnReq = va_arg(ap, int);

      if( sqlite3GlobalConfig.mnReq<1 ){
        sqlite3GlobalConfig.mnReq = 1;
      }else if( sqlite3GlobalConfig.mnReq>(1<<12) ){
        /* cap min request size at 2^12 */
        sqlite3GlobalConfig.mnReq = (1<<12);
      }

      if( sqlite3GlobalConfig.pHeap==0 ){
        /* If the heap pointer is NULL, then restore the malloc implementation
        ** back to NULL pointers too.  This will cause the malloc to go
        ** back to its default implementation when sqlite3_initialize() is
        ** run.
        */
        memset(&sqlite3GlobalConfig.m, 0, sizeof(sqlite3GlobalConfig.m));
      }else{
        /* The heap pointer is not NULL, then install one of the
        ** mem5.c/mem3.c methods. If neither ENABLE_MEMSYS3 nor
        ** ENABLE_MEMSYS5 is defined, return an error.
        */
#ifdef SQLITE_ENABLE_MEMSYS3
        sqlite3GlobalConfig.m = *sqlite3MemGetMemsys3();
#endif
#ifdef SQLITE_ENABLE_MEMSYS5
        sqlite3GlobalConfig.m = *sqlite3MemGetMemsys5();
#endif
      }
      break;
    }
#endif

    case SQLITE_CONFIG_LOOKASIDE: {
      sqlite3GlobalConfig.szLookaside = va_arg(ap, int);
      sqlite3GlobalConfig.nLookaside = va_arg(ap, int);
      break;
    }
    
    /* Record a pointer to the logger funcction and its first argument.
    ** The default is NULL.  Logging is disabled if the function pointer is
    ** NULL.
    */
    case SQLITE_CONFIG_LOG: {
      /* MSVC is picky about pulling func ptrs from va lists.
      ** http://support.microsoft.com/kb/47961
      ** sqlite3GlobalConfig.xLog = va_arg(ap, void(*)(void*,int,const char*));
      */
      typedef void(*LOGFUNC_t)(void*,int,const char*);
      sqlite3GlobalConfig.xLog = va_arg(ap, LOGFUNC_t);
      sqlite3GlobalConfig.pLogArg = va_arg(ap, void*);
      break;
    }

    case SQLITE_CONFIG_URI: {
      sqlite3GlobalConfig.bOpenUri = va_arg(ap, int);
      break;
    }

    case SQLITE_CONFIG_COVERING_INDEX_SCAN: {
      sqlite3GlobalConfig.bUseCis = va_arg(ap, int);
      break;
    }

#ifdef SQLITE_ENABLE_SQLLOG
    case SQLITE_CONFIG_SQLLOG: {
      typedef void(*SQLLOGFUNC_t)(void*, sqlite3*, const char*, int);
      sqlite3GlobalConfig.xSqllog = va_arg(ap, SQLLOGFUNC_t);
      sqlite3GlobalConfig.pSqllogArg = va_arg(ap, void *);
      break;
    }
#endif

    default: {
      rc = SQLITE_ERROR;
      break;
    }
  }
