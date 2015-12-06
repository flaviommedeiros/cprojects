#ifndef SQLITE_OMIT_HEX_INTEGER
if( z[0]=='0'
   && (z[1]=='x' || z[1]=='X')
   && sqlite3Isxdigit(z[2])
  ){
    u64 u = 0;
    int i, k;
    for(i=2; z[i]=='0'; i++){}
    for(k=i; sqlite3Isxdigit(z[k]); k++){
      u = u*16 + sqlite3HexToInt(z[k]);
    }
    memcpy(pOut, &u, 8);
    return (z[k]==0 && k-i<=16) ? 0 : 1;
  }else
#endif /* SQLITE_OMIT_HEX_INTEGER */
  {
    return sqlite3Atoi64(z, pOut, sqlite3Strlen30(z), SQLITE_UTF8);
  }
