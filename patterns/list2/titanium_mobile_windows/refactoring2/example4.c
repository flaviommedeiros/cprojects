#if !defined(SQLITE_DEBUG) && !defined(SQLITE_ENABLE_STMT_SCANSTATUS)
if( pParse->explain==2 )
#endif
  {
    struct SrcList_item *pItem = &pTabList->a[pLevel->iFrom];
    Vdbe *v = pParse->pVdbe;      /* VM being constructed */
    sqlite3 *db = pParse->db;     /* Database handle */
    int iId = pParse->iSelectId;  /* Select id (left-most output column) */
    int isSearch;                 /* True for a SEARCH. False for SCAN. */
    WhereLoop *pLoop;             /* The controlling WhereLoop object */
    u32 flags;                    /* Flags that describe this loop */
    char *zMsg;                   /* Text to add to EQP output */
    StrAccum str;                 /* EQP output string */
    char zBuf[100];               /* Initial space for EQP output string */

    pLoop = pLevel->pWLoop;
    flags = pLoop->wsFlags;
    if( (flags&WHERE_MULTI_OR) || (wctrlFlags&WHERE_ONETABLE_ONLY) ) return 0;

    isSearch = (flags&(WHERE_BTM_LIMIT|WHERE_TOP_LIMIT))!=0
            || ((flags&WHERE_VIRTUALTABLE)==0 && (pLoop->u.btree.nEq>0))
            || (wctrlFlags&(WHERE_ORDERBY_MIN|WHERE_ORDERBY_MAX));

    sqlite3StrAccumInit(&str, db, zBuf, sizeof(zBuf), SQLITE_MAX_LENGTH);
    sqlite3StrAccumAppendAll(&str, isSearch ? "SEARCH" : "SCAN");
    if( pItem->pSelect ){
      sqlite3XPrintf(&str, 0, " SUBQUERY %d", pItem->iSelectId);
    }else{
      sqlite3XPrintf(&str, 0, " TABLE %s", pItem->zName);
    }

    if( pItem->zAlias ){
      sqlite3XPrintf(&str, 0, " AS %s", pItem->zAlias);
    }
    if( (flags & (WHERE_IPK|WHERE_VIRTUALTABLE))==0 ){
      const char *zFmt = 0;
      Index *pIdx;

      assert( pLoop->u.btree.pIndex!=0 );
      pIdx = pLoop->u.btree.pIndex;
      assert( !(flags&WHERE_AUTO_INDEX) || (flags&WHERE_IDX_ONLY) );
      if( !HasRowid(pItem->pTab) && IsPrimaryKeyIndex(pIdx) ){
        if( isSearch ){
          zFmt = "PRIMARY KEY";
        }
      }else if( flags & WHERE_PARTIALIDX ){
        zFmt = "AUTOMATIC PARTIAL COVERING INDEX";
      }else if( flags & WHERE_AUTO_INDEX ){
        zFmt = "AUTOMATIC COVERING INDEX";
      }else if( flags & WHERE_IDX_ONLY ){
        zFmt = "COVERING INDEX %s";
      }else{
        zFmt = "INDEX %s";
      }
      if( zFmt ){
        sqlite3StrAccumAppend(&str, " USING ", 7);
        sqlite3XPrintf(&str, 0, zFmt, pIdx->zName);
        explainIndexRange(&str, pLoop);
      }
    }else if( (flags & WHERE_IPK)!=0 && (flags & WHERE_CONSTRAINT)!=0 ){
      const char *zRangeOp;
      if( flags&(WHERE_COLUMN_EQ|WHERE_COLUMN_IN) ){
        zRangeOp = "=";
      }else if( (flags&WHERE_BOTH_LIMIT)==WHERE_BOTH_LIMIT ){
        zRangeOp = ">? AND rowid<";
      }else if( flags&WHERE_BTM_LIMIT ){
        zRangeOp = ">";
      }else{
        assert( flags&WHERE_TOP_LIMIT);
        zRangeOp = "<";
      }
      sqlite3XPrintf(&str, 0, " USING INTEGER PRIMARY KEY (rowid%s?)",zRangeOp);
    }
#ifndef SQLITE_OMIT_VIRTUALTABLE
    else if( (flags & WHERE_VIRTUALTABLE)!=0 ){
      sqlite3XPrintf(&str, 0, " VIRTUAL TABLE INDEX %d:%s",
                  pLoop->u.vtab.idxNum, pLoop->u.vtab.idxStr);
    }
#endif
#ifdef SQLITE_EXPLAIN_ESTIMATED_ROWS
    if( pLoop->nOut>=10 ){
      sqlite3XPrintf(&str, 0, " (~%llu rows)", sqlite3LogEstToInt(pLoop->nOut));
    }else{
      sqlite3StrAccumAppend(&str, " (~1 row)", 9);
    }
#endif
    zMsg = sqlite3StrAccumFinish(&str);
    ret = sqlite3VdbeAddOp4(v, OP_Explain, iId, iLevel, iFrom, zMsg,P4_DYNAMIC);
  }
