#ifndef NDEBUG
if( sqlite3StrICmp(zLeft, "parser_trace")==0 ){
    if( zRight ){
      if( sqlite3GetBoolean(zRight, 0) ){
        sqlite3ParserTrace(stderr, "parser: ");
      }else{
        sqlite3ParserTrace(0, 0);
      }
    }
  }else
#endif

  /* Reinstall the LIKE and GLOB functions.  The variant of LIKE
  ** used will be case sensitive or not depending on the RHS.
  */
  if( sqlite3StrICmp(zLeft, "case_sensitive_like")==0 ){
    if( zRight ){
      sqlite3RegisterLikeFunctions(db, sqlite3GetBoolean(zRight, 0));
    }
  }else

#ifndef SQLITE_INTEGRITY_CHECK_ERROR_MAX
# define SQLITE_INTEGRITY_CHECK_ERROR_MAX 100
#endif

#ifndef SQLITE_OMIT_INTEGRITY_CHECK
  /* Pragma "quick_check" is an experimental reduced version of 
  ** integrity_check designed to detect most database corruption
  ** without most of the overhead of a full integrity-check.
  */
  if( sqlite3StrICmp(zLeft, "integrity_check")==0
   || sqlite3StrICmp(zLeft, "quick_check")==0 
  ){
    int i, j, addr, mxErr;

    /* Code that appears at the end of the integrity check.  If no error
    ** messages have been generated, output OK.  Otherwise output the
    ** error message
    */
    static const VdbeOpList endCode[] = {
      { OP_AddImm,      1, 0,        0},    /* 0 */
      { OP_IfNeg,       1, 0,        0},    /* 1 */
      { OP_String8,     0, 3,        0},    /* 2 */
      { OP_ResultRow,   3, 1,        0},
    };

    int isQuick = (sqlite3Tolower(zLeft[0])=='q');

    /* If the PRAGMA command was of the form "PRAGMA <db>.integrity_check",
    ** then iDb is set to the index of the database identified by <db>.
    ** In this case, the integrity of database iDb only is verified by
    ** the VDBE created below.
    **
    ** Otherwise, if the command was simply "PRAGMA integrity_check" (or
    ** "PRAGMA quick_check"), then iDb is set to 0. In this case, set iDb
    ** to -1 here, to indicate that the VDBE should verify the integrity
    ** of all attached databases.  */
    assert( iDb>=0 );
    assert( iDb==0 || pId2->z );
    if( pId2->z==0 ) iDb = -1;

    /* Initialize the VDBE program */
    if( sqlite3ReadSchema(pParse) ) goto pragma_out;
    pParse->nMem = 6;
    sqlite3VdbeSetNumCols(v, 1);
    sqlite3VdbeSetColName(v, 0, COLNAME_NAME, "integrity_check", SQLITE_STATIC);

    /* Set the maximum error count */
    mxErr = SQLITE_INTEGRITY_CHECK_ERROR_MAX;
    if( zRight ){
      sqlite3GetInt32(zRight, &mxErr);
      if( mxErr<=0 ){
        mxErr = SQLITE_INTEGRITY_CHECK_ERROR_MAX;
      }
    }
    sqlite3VdbeAddOp2(v, OP_Integer, mxErr, 1);  /* reg[1] holds errors left */

    /* Do an integrity check on each database file */
    for(i=0; i<db->nDb; i++){
      HashElem *x;
      Hash *pTbls;
      int cnt = 0;

      if( OMIT_TEMPDB && i==1 ) continue;
      if( iDb>=0 && i!=iDb ) continue;

      sqlite3CodeVerifySchema(pParse, i);
      addr = sqlite3VdbeAddOp1(v, OP_IfPos, 1); /* Halt if out of errors */
      sqlite3VdbeAddOp2(v, OP_Halt, 0, 0);
      sqlite3VdbeJumpHere(v, addr);

      /* Do an integrity check of the B-Tree
      **
      ** Begin by filling registers 2, 3, ... with the root pages numbers
      ** for all tables and indices in the database.
      */
      assert( sqlite3SchemaMutexHeld(db, i, 0) );
      pTbls = &db->aDb[i].pSchema->tblHash;
      for(x=sqliteHashFirst(pTbls); x; x=sqliteHashNext(x)){
        Table *pTab = sqliteHashData(x);
        Index *pIdx;
        sqlite3VdbeAddOp2(v, OP_Integer, pTab->tnum, 2+cnt);
        cnt++;
        for(pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext){
          sqlite3VdbeAddOp2(v, OP_Integer, pIdx->tnum, 2+cnt);
          cnt++;
        }
      }

      /* Make sure sufficient number of registers have been allocated */
      if( pParse->nMem < cnt+4 ){
        pParse->nMem = cnt+4;
      }

      /* Do the b-tree integrity checks */
      sqlite3VdbeAddOp3(v, OP_IntegrityCk, 2, cnt, 1);
      sqlite3VdbeChangeP5(v, (u8)i);
      addr = sqlite3VdbeAddOp1(v, OP_IsNull, 2);
      sqlite3VdbeAddOp4(v, OP_String8, 0, 3, 0,
         sqlite3MPrintf(db, "*** in database %s ***\n", db->aDb[i].zName),
         P4_DYNAMIC);
      sqlite3VdbeAddOp2(v, OP_Move, 2, 4);
      sqlite3VdbeAddOp3(v, OP_Concat, 4, 3, 2);
      sqlite3VdbeAddOp2(v, OP_ResultRow, 2, 1);
      sqlite3VdbeJumpHere(v, addr);

      /* Make sure all the indices are constructed correctly.
      */
      for(x=sqliteHashFirst(pTbls); x && !isQuick; x=sqliteHashNext(x)){
        Table *pTab = sqliteHashData(x);
        Index *pIdx;
        int loopTop;

        if( pTab->pIndex==0 ) continue;
        addr = sqlite3VdbeAddOp1(v, OP_IfPos, 1);  /* Stop if out of errors */
        sqlite3VdbeAddOp2(v, OP_Halt, 0, 0);
        sqlite3VdbeJumpHere(v, addr);
        sqlite3OpenTableAndIndices(pParse, pTab, 1, OP_OpenRead);
        sqlite3VdbeAddOp2(v, OP_Integer, 0, 2);  /* reg(2) will count entries */
        loopTop = sqlite3VdbeAddOp2(v, OP_Rewind, 1, 0);
        sqlite3VdbeAddOp2(v, OP_AddImm, 2, 1);   /* increment entry count */
        for(j=0, pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext, j++){
          int jmp2;
          int r1;
          static const VdbeOpList idxErr[] = {
            { OP_AddImm,      1, -1,  0},
            { OP_String8,     0,  3,  0},    /* 1 */
            { OP_Rowid,       1,  4,  0},
            { OP_String8,     0,  5,  0},    /* 3 */
            { OP_String8,     0,  6,  0},    /* 4 */
            { OP_Concat,      4,  3,  3},
            { OP_Concat,      5,  3,  3},
            { OP_Concat,      6,  3,  3},
            { OP_ResultRow,   3,  1,  0},
            { OP_IfPos,       1,  0,  0},    /* 9 */
            { OP_Halt,        0,  0,  0},
          };
          r1 = sqlite3GenerateIndexKey(pParse, pIdx, 1, 3, 0);
          jmp2 = sqlite3VdbeAddOp4Int(v, OP_Found, j+2, 0, r1, pIdx->nColumn+1);
          addr = sqlite3VdbeAddOpList(v, ArraySize(idxErr), idxErr);
          sqlite3VdbeChangeP4(v, addr+1, "rowid ", P4_STATIC);
          sqlite3VdbeChangeP4(v, addr+3, " missing from index ", P4_STATIC);
          sqlite3VdbeChangeP4(v, addr+4, pIdx->zName, P4_TRANSIENT);
          sqlite3VdbeJumpHere(v, addr+9);
          sqlite3VdbeJumpHere(v, jmp2);
        }
        sqlite3VdbeAddOp2(v, OP_Next, 1, loopTop+1);
        sqlite3VdbeJumpHere(v, loopTop);
        for(j=0, pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext, j++){
          static const VdbeOpList cntIdx[] = {
             { OP_Integer,      0,  3,  0},
             { OP_Rewind,       0,  0,  0},  /* 1 */
             { OP_AddImm,       3,  1,  0},
             { OP_Next,         0,  0,  0},  /* 3 */
             { OP_Eq,           2,  0,  3},  /* 4 */
             { OP_AddImm,       1, -1,  0},
             { OP_String8,      0,  2,  0},  /* 6 */
             { OP_String8,      0,  3,  0},  /* 7 */
             { OP_Concat,       3,  2,  2},
             { OP_ResultRow,    2,  1,  0},
          };
          addr = sqlite3VdbeAddOp1(v, OP_IfPos, 1);
          sqlite3VdbeAddOp2(v, OP_Halt, 0, 0);
          sqlite3VdbeJumpHere(v, addr);
          addr = sqlite3VdbeAddOpList(v, ArraySize(cntIdx), cntIdx);
          sqlite3VdbeChangeP1(v, addr+1, j+2);
          sqlite3VdbeChangeP2(v, addr+1, addr+4);
          sqlite3VdbeChangeP1(v, addr+3, j+2);
          sqlite3VdbeChangeP2(v, addr+3, addr+2);
          sqlite3VdbeJumpHere(v, addr+4);
          sqlite3VdbeChangeP4(v, addr+6, 
                     "wrong # of entries in index ", P4_STATIC);
          sqlite3VdbeChangeP4(v, addr+7, pIdx->zName, P4_TRANSIENT);
        }
      } 
    }
    addr = sqlite3VdbeAddOpList(v, ArraySize(endCode), endCode);
    sqlite3VdbeChangeP2(v, addr, -mxErr);
    sqlite3VdbeJumpHere(v, addr+1);
    sqlite3VdbeChangeP4(v, addr+2, "ok", P4_STATIC);
  }else
#endif /* SQLITE_OMIT_INTEGRITY_CHECK */

#ifndef SQLITE_OMIT_UTF16
  /*
  **   PRAGMA encoding
  **   PRAGMA encoding = "utf-8"|"utf-16"|"utf-16le"|"utf-16be"
  **
  ** In its first form, this pragma returns the encoding of the main
  ** database. If the database is not initialized, it is initialized now.
  **
  ** The second form of this pragma is a no-op if the main database file
  ** has not already been initialized. In this case it sets the default
  ** encoding that will be used for the main database file if a new file
  ** is created. If an existing main database file is opened, then the
  ** default text encoding for the existing database is used.
  ** 
  ** In all cases new databases created using the ATTACH command are
  ** created to use the same default text encoding as the main database. If
  ** the main database has not been initialized and/or created when ATTACH
  ** is executed, this is done before the ATTACH operation.
  **
  ** In the second form this pragma sets the text encoding to be used in
  ** new database files created using this database handle. It is only
  ** useful if invoked immediately after the main database i
  */
  if( sqlite3StrICmp(zLeft, "encoding")==0 ){
    static const struct EncName {
      char *zName;
      u8 enc;
    } encnames[] = {
      { "UTF8",     SQLITE_UTF8        },
      { "UTF-8",    SQLITE_UTF8        },  /* Must be element [1] */
      { "UTF-16le", SQLITE_UTF16LE     },  /* Must be element [2] */
      { "UTF-16be", SQLITE_UTF16BE     },  /* Must be element [3] */
      { "UTF16le",  SQLITE_UTF16LE     },
      { "UTF16be",  SQLITE_UTF16BE     },
      { "UTF-16",   0                  }, /* SQLITE_UTF16NATIVE */
      { "UTF16",    0                  }, /* SQLITE_UTF16NATIVE */
      { 0, 0 }
    };
    const struct EncName *pEnc;
    if( !zRight ){    /* "PRAGMA encoding" */
      if( sqlite3ReadSchema(pParse) ) goto pragma_out;
      sqlite3VdbeSetNumCols(v, 1);
      sqlite3VdbeSetColName(v, 0, COLNAME_NAME, "encoding", SQLITE_STATIC);
      sqlite3VdbeAddOp2(v, OP_String8, 0, 1);
      assert( encnames[SQLITE_UTF8].enc==SQLITE_UTF8 );
      assert( encnames[SQLITE_UTF16LE].enc==SQLITE_UTF16LE );
      assert( encnames[SQLITE_UTF16BE].enc==SQLITE_UTF16BE );
      sqlite3VdbeChangeP4(v, -1, encnames[ENC(pParse->db)].zName, P4_STATIC);
      sqlite3VdbeAddOp2(v, OP_ResultRow, 1, 1);
    }else{                        /* "PRAGMA encoding = XXX" */
      /* Only change the value of sqlite.enc if the database handle is not
      ** initialized. If the main database exists, the new sqlite.enc value
      ** will be overwritten when the schema is next loaded. If it does not
      ** already exists, it will be created to use the new encoding value.
      */
      if( 
        !(DbHasProperty(db, 0, DB_SchemaLoaded)) || 
        DbHasProperty(db, 0, DB_Empty) 
      ){
        for(pEnc=&encnames[0]; pEnc->zName; pEnc++){
          if( 0==sqlite3StrICmp(zRight, pEnc->zName) ){
            ENC(pParse->db) = pEnc->enc ? pEnc->enc : SQLITE_UTF16NATIVE;
            break;
          }
        }
        if( !pEnc->zName ){
          sqlite3ErrorMsg(pParse, "unsupported encoding: %s", zRight);
        }
      }
    }
  }else
#endif /* SQLITE_OMIT_UTF16 */

#ifndef SQLITE_OMIT_SCHEMA_VERSION_PRAGMAS
  /*
  **   PRAGMA [database.]schema_version
  **   PRAGMA [database.]schema_version = <integer>
  **
  **   PRAGMA [database.]user_version
  **   PRAGMA [database.]user_version = <integer>
  **
  **   PRAGMA [database.]freelist_count = <integer>
  **
  **   PRAGMA [database.]application_id
  **   PRAGMA [database.]application_id = <integer>
  **
  ** The pragma's schema_version and user_version are used to set or get
  ** the value of the schema-version and user-version, respectively. Both
  ** the schema-version and the user-version are 32-bit signed integers
  ** stored in the database header.
  **
  ** The schema-cookie is usually only manipulated internally by SQLite. It
  ** is incremented by SQLite whenever the database schema is modified (by
  ** creating or dropping a table or index). The schema version is used by
  ** SQLite each time a query is executed to ensure that the internal cache
  ** of the schema used when compiling the SQL query matches the schema of
  ** the database against which the compiled query is actually executed.
  ** Subverting this mechanism by using "PRAGMA schema_version" to modify
  ** the schema-version is potentially dangerous and may lead to program
  ** crashes or database corruption. Use with caution!
  **
  ** The user-version is not used internally by SQLite. It may be used by
  ** applications for any purpose.
  */
  if( sqlite3StrICmp(zLeft, "schema_version")==0 
   || sqlite3StrICmp(zLeft, "user_version")==0 
   || sqlite3StrICmp(zLeft, "freelist_count")==0 
   || sqlite3StrICmp(zLeft, "application_id")==0 
  ){
    int iCookie;   /* Cookie index. 1 for schema-cookie, 6 for user-cookie. */
    sqlite3VdbeUsesBtree(v, iDb);
    switch( zLeft[0] ){
      case 'a': case 'A':
        iCookie = BTREE_APPLICATION_ID;
        break;
      case 'f': case 'F':
        iCookie = BTREE_FREE_PAGE_COUNT;
        break;
      case 's': case 'S':
        iCookie = BTREE_SCHEMA_VERSION;
        break;
      default:
        iCookie = BTREE_USER_VERSION;
        break;
    }

    if( zRight && iCookie!=BTREE_FREE_PAGE_COUNT ){
      /* Write the specified cookie value */
      static const VdbeOpList setCookie[] = {
        { OP_Transaction,    0,  1,  0},    /* 0 */
        { OP_Integer,        0,  1,  0},    /* 1 */
        { OP_SetCookie,      0,  0,  1},    /* 2 */
      };
      int addr = sqlite3VdbeAddOpList(v, ArraySize(setCookie), setCookie);
      sqlite3VdbeChangeP1(v, addr, iDb);
      sqlite3VdbeChangeP1(v, addr+1, sqlite3Atoi(zRight));
      sqlite3VdbeChangeP1(v, addr+2, iDb);
      sqlite3VdbeChangeP2(v, addr+2, iCookie);
    }else{
      /* Read the specified cookie value */
      static const VdbeOpList readCookie[] = {
        { OP_Transaction,     0,  0,  0},    /* 0 */
        { OP_ReadCookie,      0,  1,  0},    /* 1 */
        { OP_ResultRow,       1,  1,  0}
      };
      int addr = sqlite3VdbeAddOpList(v, ArraySize(readCookie), readCookie);
      sqlite3VdbeChangeP1(v, addr, iDb);
      sqlite3VdbeChangeP1(v, addr+1, iDb);
      sqlite3VdbeChangeP3(v, addr+1, iCookie);
      sqlite3VdbeSetNumCols(v, 1);
      sqlite3VdbeSetColName(v, 0, COLNAME_NAME, zLeft, SQLITE_TRANSIENT);
    }
  }else
#endif /* SQLITE_OMIT_SCHEMA_VERSION_PRAGMAS */

#ifndef SQLITE_OMIT_COMPILEOPTION_DIAGS
  /*
  **   PRAGMA compile_options
  **
  ** Return the names of all compile-time options used in this build,
  ** one option per row.
  */
  if( sqlite3StrICmp(zLeft, "compile_options")==0 ){
    int i = 0;
    const char *zOpt;
    sqlite3VdbeSetNumCols(v, 1);
    pParse->nMem = 1;
    sqlite3VdbeSetColName(v, 0, COLNAME_NAME, "compile_option", SQLITE_STATIC);
    while( (zOpt = sqlite3_compileoption_get(i++))!=0 ){
      sqlite3VdbeAddOp4(v, OP_String8, 0, 1, 0, zOpt, 0);
      sqlite3VdbeAddOp2(v, OP_ResultRow, 1, 1);
    }
  }else
#endif /* SQLITE_OMIT_COMPILEOPTION_DIAGS */

#ifndef SQLITE_OMIT_WAL
  /*
  **   PRAGMA [database.]wal_checkpoint = passive|full|restart
  **
  ** Checkpoint the database.
  */
  if( sqlite3StrICmp(zLeft, "wal_checkpoint")==0 ){
    int iBt = (pId2->z?iDb:SQLITE_MAX_ATTACHED);
    int eMode = SQLITE_CHECKPOINT_PASSIVE;
    if( zRight ){
      if( sqlite3StrICmp(zRight, "full")==0 ){
        eMode = SQLITE_CHECKPOINT_FULL;
      }else if( sqlite3StrICmp(zRight, "restart")==0 ){
        eMode = SQLITE_CHECKPOINT_RESTART;
      }
    }
    if( sqlite3ReadSchema(pParse) ) goto pragma_out;
    sqlite3VdbeSetNumCols(v, 3);
    pParse->nMem = 3;
    sqlite3VdbeSetColName(v, 0, COLNAME_NAME, "busy", SQLITE_STATIC);
    sqlite3VdbeSetColName(v, 1, COLNAME_NAME, "log", SQLITE_STATIC);
    sqlite3VdbeSetColName(v, 2, COLNAME_NAME, "checkpointed", SQLITE_STATIC);

    sqlite3VdbeAddOp3(v, OP_Checkpoint, iBt, eMode, 1);
    sqlite3VdbeAddOp2(v, OP_ResultRow, 1, 3);
  }else

  /*
  **   PRAGMA wal_autocheckpoint
  **   PRAGMA wal_autocheckpoint = N
  **
  ** Configure a database connection to automatically checkpoint a database
  ** after accumulating N frames in the log. Or query for the current value
  ** of N.
  */
  if( sqlite3StrICmp(zLeft, "wal_autocheckpoint")==0 ){
    if( zRight ){
      sqlite3_wal_autocheckpoint(db, sqlite3Atoi(zRight));
    }
    returnSingleInt(pParse, "wal_autocheckpoint", 
       db->xWalCallback==sqlite3WalDefaultHook ? 
           SQLITE_PTR_TO_INT(db->pWalArg) : 0);
  }else
#endif

  /*
  **  PRAGMA shrink_memory
  **
  ** This pragma attempts to free as much memory as possible from the
  ** current database connection.
  */
  if( sqlite3StrICmp(zLeft, "shrink_memory")==0 ){
    sqlite3_db_release_memory(db);
  }else

  /*
  **   PRAGMA busy_timeout
  **   PRAGMA busy_timeout = N
  **
  ** Call sqlite3_busy_timeout(db, N).  Return the current timeout value
  ** if one is set.  If no busy handler or a different busy handler is set
  ** then 0 is returned.  Setting the busy_timeout to 0 or negative
  ** disables the timeout.
  */
  if( sqlite3StrICmp(zLeft, "busy_timeout")==0 ){
    if( zRight ){
      sqlite3_busy_timeout(db, sqlite3Atoi(zRight));
    }
    returnSingleInt(pParse, "timeout",  db->busyTimeout);
  }else

#if defined(SQLITE_DEBUG) || defined(SQLITE_TEST)
  /*
  ** Report the current state of file logs for all databases
  */
  if( sqlite3StrICmp(zLeft, "lock_status")==0 ){
    static const char *const azLockName[] = {
      "unlocked", "shared", "reserved", "pending", "exclusive"
    };
    int i;
    sqlite3VdbeSetNumCols(v, 2);
    pParse->nMem = 2;
    sqlite3VdbeSetColName(v, 0, COLNAME_NAME, "database", SQLITE_STATIC);
    sqlite3VdbeSetColName(v, 1, COLNAME_NAME, "status", SQLITE_STATIC);
    for(i=0; i<db->nDb; i++){
      Btree *pBt;
      const char *zState = "unknown";
      int j;
      if( db->aDb[i].zName==0 ) continue;
      sqlite3VdbeAddOp4(v, OP_String8, 0, 1, 0, db->aDb[i].zName, P4_STATIC);
      pBt = db->aDb[i].pBt;
      if( pBt==0 || sqlite3BtreePager(pBt)==0 ){
        zState = "closed";
      }else if( sqlite3_file_control(db, i ? db->aDb[i].zName : 0, 
                                     SQLITE_FCNTL_LOCKSTATE, &j)==SQLITE_OK ){
         zState = azLockName[j];
      }
      sqlite3VdbeAddOp4(v, OP_String8, 0, 2, 0, zState, P4_STATIC);
      sqlite3VdbeAddOp2(v, OP_ResultRow, 1, 2);
    }

  }else
#endif

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
  if( sqlite3StrICmp(zLeft, "activate_extensions")==0 && zRight ){
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
