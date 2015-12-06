if( sqlite3Fts3HashInsert(pHash, "simple", 7, (void *)pSimple)
     || sqlite3Fts3HashInsert(pHash, "porter", 7, (void *)pPorter) 
#ifdef SQLITE_ENABLE_ICU
     || (pIcu && sqlite3Fts3HashInsert(pHash, "icu", 4, (void *)pIcu))
#endif
    ){
      rc = SQLITE_NOMEM;
    }
