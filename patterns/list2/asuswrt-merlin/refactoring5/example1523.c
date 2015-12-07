#ifndef SQLITE_OMIT_MEMORYDB
if( strcmp(zFilename,":memory:")==0 ){
      memDb = 1;
      zPathname[0] = 0;
    }else
#endif
    {
      zPathname[0] = 0; /* Make sure initialized even if FullPathname() fails */
      rc = sqlite3OsFullPathname(pVfs, zFilename, nPathname, zPathname);
    }
