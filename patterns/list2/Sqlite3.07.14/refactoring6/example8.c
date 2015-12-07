if( rc!=SQLITE_OK
   || (rc = sqlite3_create_function(db, zName, 1, any, p, scalarFunc, 0, 0))
   || (rc = sqlite3_create_function(db, zName, 2, any, p, scalarFunc, 0, 0))
#ifdef SQLITE_TEST
   || (rc = sqlite3_create_function(db, zTest, 2, any, p, testFunc, 0, 0))
   || (rc = sqlite3_create_function(db, zTest, 3, any, p, testFunc, 0, 0))
   || (rc = sqlite3_create_function(db, zTest2, 0, any, pdb, intTestFunc, 0, 0))
#endif
  );
