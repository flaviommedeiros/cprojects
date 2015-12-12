#if SQLITE_ENABLE_8_3_NAMES<2
if( zOk && sqlite3GetBoolean(zOk) )
#endif
  {
    int i, sz;
    sz = sqlite3Strlen30(z);
    for(i=sz-1; i>0 && z[i]!='/' && z[i]!='.'; i--){}
    if( z[i]=='.' && ALWAYS(sz>i+4) ) memcpy(&z[i+1], &z[sz-3], 4);
  }
