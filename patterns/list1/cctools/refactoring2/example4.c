#ifndef SQLITE_OMIT_FLOATING_POINT
if( !sqlite3Isdigit(z[1]) )
#endif
      {
        *tokenType = TK_DOT;
        return 1;
      }
