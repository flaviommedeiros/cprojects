#ifdef SQLITE_HAS_CODEC
if( sqlite3StrICmp(zLeft, "key")==0 && zRight ){
    sqlite3_key(db, zRight, sqlite3Strlen30(zRight));
  }else
  if( sqlite3StrICmp(zLeft, "rekey")==0 && zRight ){
    sqlite3_rekey(db, zRight, sqlite3Strlen30(zRight));
  }else
  if( zRight && (sqlite3StrICmp(zLeft, "hexkey")==0 ||
                 sqlite3StrICmp(zLeft, "hexrekey")==0) ){
    int i, h1, h2;
    char zKey[40];
    for(i=0; (h1 = zRight[i])!=0 && (h2 = zRight[i+1])!=0; i+=2){
      h1 += 9*(1&(h1>>6));
      h2 += 9*(1&(h2>>6));
      zKey[i/2] = (h2 & 0x0f) | ((h1 & 0xf)<<4);
    }
    if( (zLeft[3] & 0xf)==0xb ){
      sqlite3_key(db, zKey, i/2);
    }else{
      sqlite3_rekey(db, zKey, i/2);
    }
  }else
#endif
#if defined(SQLITE_HAS_CODEC) || defined(SQLITE_ENABLE_CEROD)
  if( sqlite3StrICmp(zLeft, "activate_extensions")==0 ){
#ifdef SQLITE_HAS_CODEC
    if( sqlite3StrNICmp(zRight, "see-", 4)==0 ){
      sqlite3_activate_see(&zRight[4]);
    }
#endif
#ifdef SQLITE_ENABLE_CEROD
    if( sqlite3StrNICmp(zRight, "cerod-", 6)==0 ){
      sqlite3_activate_cerod(&zRight[6]);
    }
#endif
  }else
#endif

 
  {/* Empty ELSE clause */}
