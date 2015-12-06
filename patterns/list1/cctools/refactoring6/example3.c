if( sqlite3StrNICmp(pTab->zName, "sqlite_", 7)==0 
       && db->init.busy==0
#if SQLITE_USER_AUTHENTICATION
       && sqlite3UserAuthTable(pTab->zName)==0
#endif
       && sqlite3StrNICmp(&pTab->zName[7],"altertab_",9)!=0 ){
    sqlite3ErrorMsg(pParse, "table %s may not be indexed", pTab->zName);
    goto exit_create_index;
  }
