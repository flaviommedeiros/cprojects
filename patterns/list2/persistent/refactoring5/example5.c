#ifndef SQLITE_OMIT_HEX_INTEGER
if( sqlite3_strnicmp(z,"0x",2)==0 ){
        sqlite3ErrorMsg(pParse, "hex literal too big: %s", z);
      }else
#endif
      {
        codeReal(v, z, negFlag, iMem);
      }
