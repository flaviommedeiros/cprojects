if( sqlite3Fts3HashInsert(pHash, "simple", 7, (void *)pSimple)
     || sqlite3Fts3HashInsert(pHash, "porter", 7, (void *)pPorter) 

#ifdef SQLITE_ENABLE_FTS4_UNICODE61
     || sqlite3Fts3HashInsert(pHash, "unicode61", 10, (void *)pUnicode) 
#endif
#ifdef SQLITE_ENABLE_ICU
     || (pIcu && sqlite3Fts3HashInsert(pHash, "icu", 4, (void *)pIcu))
#endif
    ){
      rc = SQLITE_NOMEM;
    }
