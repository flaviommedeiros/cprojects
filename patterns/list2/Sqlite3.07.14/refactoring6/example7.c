if( SQLITE_OK==rc 
   && SQLITE_OK==(rc = sqlite3Fts2InitHashTable(db, pHash, "fts2_tokenizer"))
   && SQLITE_OK==(rc = sqlite3_overload_function(db, "snippet", -1))
   && SQLITE_OK==(rc = sqlite3_overload_function(db, "offsets", -1))
   && SQLITE_OK==(rc = sqlite3_overload_function(db, "optimize", -1))
#ifdef SQLITE_TEST
   && SQLITE_OK==(rc = sqlite3_overload_function(db, "dump_terms", -1))
   && SQLITE_OK==(rc = sqlite3_overload_function(db, "dump_doclist", -1))
#endif
  ){
    return sqlite3_create_module_v2(
        db, "fts2", &fts2Module, (void *)pHash, hashDestroy
    );
  }
