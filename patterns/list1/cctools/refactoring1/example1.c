if( strcmp(z, "unixepoch")==0 && p->validJD ){
        p->iJD = (p->iJD + 43200)/86400 + 21086676*(i64)10000000;
        clearYMD_HMS_TZ(p);
        rc = 0;
      }
#ifndef SQLITE_OMIT_LOCALTIME
      else if( strcmp(z, "utc")==0 ){
        sqlite3_int64 c1;
        computeJD(p);
        c1 = localtimeOffset(p, pCtx, &rc);
        if( rc==SQLITE_OK ){
          p->iJD -= c1;
          clearYMD_HMS_TZ(p);
          p->iJD += c1 - localtimeOffset(p, pCtx, &rc);
        }
      }
#endif
