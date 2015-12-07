#ifndef SQLITE_OMIT_VIRTUALTABLE
if(  (pLevel->plan.wsFlags & WHERE_VIRTUALTABLE)!=0 ){
    /* Case 0:  The table is a virtual-table.  Use the VFilter and VNext
    **          to access the data.
    */
    int iReg;   /* P3 Value for OP_VFilter */
    sqlite3_index_info *pVtabIdx = pLevel->plan.u.pVtabIdx;
    int nConstraint = pVtabIdx->nConstraint;
    struct sqlite3_index_constraint_usage *aUsage =
                                                pVtabIdx->aConstraintUsage;
    const struct sqlite3_index_constraint *aConstraint =
                                                pVtabIdx->aConstraint;

    sqlite3ExprCachePush(pParse);
    iReg = sqlite3GetTempRange(pParse, nConstraint+2);
    for(j=1; j<=nConstraint; j++){
      for(k=0; k<nConstraint; k++){
        if( aUsage[k].argvIndex==j ){
          int iTerm = aConstraint[k].iTermOffset;
          sqlite3ExprCode(pParse, pWC->a[iTerm].pExpr->pRight, iReg+j+1);
          break;
        }
      }
      if( k==nConstraint ) break;
    }
    sqlite3VdbeAddOp2(v, OP_Integer, pVtabIdx->idxNum, iReg);
    sqlite3VdbeAddOp2(v, OP_Integer, j-1, iReg+1);
    sqlite3VdbeAddOp4(v, OP_VFilter, iCur, addrBrk, iReg, pVtabIdx->idxStr,
                      pVtabIdx->needToFreeIdxStr ? P4_MPRINTF : P4_STATIC);
    pVtabIdx->needToFreeIdxStr = 0;
    for(j=0; j<nConstraint; j++){
      if( aUsage[j].omit ){
        int iTerm = aConstraint[j].iTermOffset;
        disableTerm(pLevel, &pWC->a[iTerm]);
      }
    }
    pLevel->op = OP_VNext;
    pLevel->p1 = iCur;
    pLevel->p2 = sqlite3VdbeCurrentAddr(v);
    sqlite3ReleaseTempRange(pParse, iReg, nConstraint+2);
    sqlite3ExprCachePop(pParse, 1);
  }else
#endif /* SQLITE_OMIT_VIRTUALTABLE */

  if( pLevel->plan.wsFlags & WHERE_ROWID_EQ ){
    /* Case 1:  We can directly reference a single row using an
    **          equality comparison against the ROWID field.  Or
    **          we reference multiple rows using a "rowid IN (...)"
    **          construct.
    */
    iReleaseReg = sqlite3GetTempReg(pParse);
    pTerm = findTerm(pWC, iCur, -1, notReady, WO_EQ|WO_IN, 0);
    assert( pTerm!=0 );
    assert( pTerm->pExpr!=0 );
    assert( pTerm->leftCursor==iCur );
    assert( omitTable==0 );
    testcase( pTerm->wtFlags & TERM_VIRTUAL ); /* EV: R-30575-11662 */
    iRowidReg = codeEqualityTerm(pParse, pTerm, pLevel, iReleaseReg);
    addrNxt = pLevel->addrNxt;
    sqlite3VdbeAddOp2(v, OP_MustBeInt, iRowidReg, addrNxt);
    sqlite3VdbeAddOp3(v, OP_NotExists, iCur, addrNxt, iRowidReg);
    sqlite3ExprCacheStore(pParse, iCur, -1, iRowidReg);
    VdbeComment((v, "pk"));
    pLevel->op = OP_Noop;
  }else if( pLevel->plan.wsFlags & WHERE_ROWID_RANGE ){
    /* Case 2:  We have an inequality comparison against the ROWID field.
    */
    int testOp = OP_Noop;
    int start;
    int memEndValue = 0;
    WhereTerm *pStart, *pEnd;

    assert( omitTable==0 );
    pStart = findTerm(pWC, iCur, -1, notReady, WO_GT|WO_GE, 0);
    pEnd = findTerm(pWC, iCur, -1, notReady, WO_LT|WO_LE, 0);
    if( bRev ){
      pTerm = pStart;
      pStart = pEnd;
      pEnd = pTerm;
    }
    if( pStart ){
      Expr *pX;             /* The expression that defines the start bound */
      int r1, rTemp;        /* Registers for holding the start boundary */

      /* The following constant maps TK_xx codes into corresponding 
      ** seek opcodes.  It depends on a particular ordering of TK_xx
      */
      const u8 aMoveOp[] = {
           /* TK_GT */  OP_SeekGt,
           /* TK_LE */  OP_SeekLe,
           /* TK_LT */  OP_SeekLt,
           /* TK_GE */  OP_SeekGe
      };
      assert( TK_LE==TK_GT+1 );      /* Make sure the ordering.. */
      assert( TK_LT==TK_GT+2 );      /*  ... of the TK_xx values... */
      assert( TK_GE==TK_GT+3 );      /*  ... is correcct. */

      testcase( pStart->wtFlags & TERM_VIRTUAL ); /* EV: R-30575-11662 */
      pX = pStart->pExpr;
      assert( pX!=0 );
      assert( pStart->leftCursor==iCur );
      r1 = sqlite3ExprCodeTemp(pParse, pX->pRight, &rTemp);
      sqlite3VdbeAddOp3(v, aMoveOp[pX->op-TK_GT], iCur, addrBrk, r1);
      VdbeComment((v, "pk"));
      sqlite3ExprCacheAffinityChange(pParse, r1, 1);
      sqlite3ReleaseTempReg(pParse, rTemp);
      disableTerm(pLevel, pStart);
    }else{
      sqlite3VdbeAddOp2(v, bRev ? OP_Last : OP_Rewind, iCur, addrBrk);
    }
    if( pEnd ){
      Expr *pX;
      pX = pEnd->pExpr;
      assert( pX!=0 );
      assert( pEnd->leftCursor==iCur );
      testcase( pEnd->wtFlags & TERM_VIRTUAL ); /* EV: R-30575-11662 */
      memEndValue = ++pParse->nMem;
      sqlite3ExprCode(pParse, pX->pRight, memEndValue);
      if( pX->op==TK_LT || pX->op==TK_GT ){
        testOp = bRev ? OP_Le : OP_Ge;
      }else{
        testOp = bRev ? OP_Lt : OP_Gt;
      }
      disableTerm(pLevel, pEnd);
    }
    start = sqlite3VdbeCurrentAddr(v);
    pLevel->op = bRev ? OP_Prev : OP_Next;
    pLevel->p1 = iCur;
    pLevel->p2 = start;
    if( pStart==0 && pEnd==0 ){
      pLevel->p5 = SQLITE_STMTSTATUS_FULLSCAN_STEP;
    }else{
      assert( pLevel->p5==0 );
    }
    if( testOp!=OP_Noop ){
      iRowidReg = iReleaseReg = sqlite3GetTempReg(pParse);
      sqlite3VdbeAddOp2(v, OP_Rowid, iCur, iRowidReg);
      sqlite3ExprCacheStore(pParse, iCur, -1, iRowidReg);
      sqlite3VdbeAddOp3(v, testOp, memEndValue, addrBrk, iRowidReg);
      sqlite3VdbeChangeP5(v, SQLITE_AFF_NUMERIC | SQLITE_JUMPIFNULL);
    }
  }else if( pLevel->plan.wsFlags & (WHERE_COLUMN_RANGE|WHERE_COLUMN_EQ) ){
    /* Case 3: A scan using an index.
    **
    **         The WHERE clause may contain zero or more equality 
    **         terms ("==" or "IN" operators) that refer to the N
    **         left-most columns of the index. It may also contain
    **         inequality constraints (>, <, >= or <=) on the indexed
    **         column that immediately follows the N equalities. Only 
    **         the right-most column can be an inequality - the rest must
    **         use the "==" and "IN" operators. For example, if the 
    **         index is on (x,y,z), then the following clauses are all 
    **         optimized:
    **
    **            x=5
    **            x=5 AND y=10
    **            x=5 AND y<10
    **            x=5 AND y>5 AND y<10
    **            x=5 AND y=5 AND z<=10
    **
    **         The z<10 term of the following cannot be used, only
    **         the x=5 term:
    **
    **            x=5 AND z<10
    **
    **         N may be zero if there are inequality constraints.
    **         If there are no inequality constraints, then N is at
    **         least one.
    **
    **         This case is also used when there are no WHERE clause
    **         constraints but an index is selected anyway, in order
    **         to force the output order to conform to an ORDER BY.
    */  
    static const u8 aStartOp[] = {
      0,
      0,
      OP_Rewind,           /* 2: (!start_constraints && startEq &&  !bRev) */
      OP_Last,             /* 3: (!start_constraints && startEq &&   bRev) */
      OP_SeekGt,           /* 4: (start_constraints  && !startEq && !bRev) */
      OP_SeekLt,           /* 5: (start_constraints  && !startEq &&  bRev) */
      OP_SeekGe,           /* 6: (start_constraints  &&  startEq && !bRev) */
      OP_SeekLe            /* 7: (start_constraints  &&  startEq &&  bRev) */
    };
    static const u8 aEndOp[] = {
      OP_Noop,             /* 0: (!end_constraints) */
      OP_IdxGE,            /* 1: (end_constraints && !bRev) */
      OP_IdxLT             /* 2: (end_constraints && bRev) */
    };
    int nEq = pLevel->plan.nEq;  /* Number of == or IN terms */
    int isMinQuery = 0;          /* If this is an optimized SELECT min(x).. */
    int regBase;                 /* Base register holding constraint values */
    int r1;                      /* Temp register */
    WhereTerm *pRangeStart = 0;  /* Inequality constraint at range start */
    WhereTerm *pRangeEnd = 0;    /* Inequality constraint at range end */
    int startEq;                 /* True if range start uses ==, >= or <= */
    int endEq;                   /* True if range end uses ==, >= or <= */
    int start_constraints;       /* Start of range is constrained */
    int nConstraint;             /* Number of constraint terms */
    Index *pIdx;                 /* The index we will be using */
    int iIdxCur;                 /* The VDBE cursor for the index */
    int nExtraReg = 0;           /* Number of extra registers needed */
    int op;                      /* Instruction opcode */
    char *zStartAff;             /* Affinity for start of range constraint */
    char *zEndAff;               /* Affinity for end of range constraint */

    pIdx = pLevel->plan.u.pIdx;
    iIdxCur = pLevel->iIdxCur;
    k = pIdx->aiColumn[nEq];     /* Column for inequality constraints */

    /* If this loop satisfies a sort order (pOrderBy) request that 
    ** was passed to this function to implement a "SELECT min(x) ..." 
    ** query, then the caller will only allow the loop to run for
    ** a single iteration. This means that the first row returned
    ** should not have a NULL value stored in 'x'. If column 'x' is
    ** the first one after the nEq equality constraints in the index,
    ** this requires some special handling.
    */
    if( (wctrlFlags&WHERE_ORDERBY_MIN)!=0
     && (pLevel->plan.wsFlags&WHERE_ORDERBY)
     && (pIdx->nColumn>nEq)
    ){
      /* assert( pOrderBy->nExpr==1 ); */
      /* assert( pOrderBy->a[0].pExpr->iColumn==pIdx->aiColumn[nEq] ); */
      isMinQuery = 1;
      nExtraReg = 1;
    }

    /* Find any inequality constraint terms for the start and end 
    ** of the range. 
    */
    if( pLevel->plan.wsFlags & WHERE_TOP_LIMIT ){
      pRangeEnd = findTerm(pWC, iCur, k, notReady, (WO_LT|WO_LE), pIdx);
      nExtraReg = 1;
    }
    if( pLevel->plan.wsFlags & WHERE_BTM_LIMIT ){
      pRangeStart = findTerm(pWC, iCur, k, notReady, (WO_GT|WO_GE), pIdx);
      nExtraReg = 1;
    }

    /* Generate code to evaluate all constraint terms using == or IN
    ** and store the values of those terms in an array of registers
    ** starting at regBase.
    */
    regBase = codeAllEqualityTerms(
        pParse, pLevel, pWC, notReady, nExtraReg, &zStartAff
    );
    zEndAff = sqlite3DbStrDup(pParse->db, zStartAff);
    addrNxt = pLevel->addrNxt;

    /* If we are doing a reverse order scan on an ascending index, or
    ** a forward order scan on a descending index, interchange the 
    ** start and end terms (pRangeStart and pRangeEnd).
    */
    if( nEq<pIdx->nColumn && bRev==(pIdx->aSortOrder[nEq]==SQLITE_SO_ASC) ){
      SWAP(WhereTerm *, pRangeEnd, pRangeStart);
    }

    testcase( pRangeStart && pRangeStart->eOperator & WO_LE );
    testcase( pRangeStart && pRangeStart->eOperator & WO_GE );
    testcase( pRangeEnd && pRangeEnd->eOperator & WO_LE );
    testcase( pRangeEnd && pRangeEnd->eOperator & WO_GE );
    startEq = !pRangeStart || pRangeStart->eOperator & (WO_LE|WO_GE);
    endEq =   !pRangeEnd || pRangeEnd->eOperator & (WO_LE|WO_GE);
    start_constraints = pRangeStart || nEq>0;

    /* Seek the index cursor to the start of the range. */
    nConstraint = nEq;
    if( pRangeStart ){
      Expr *pRight = pRangeStart->pExpr->pRight;
      sqlite3ExprCode(pParse, pRight, regBase+nEq);
      sqlite3ExprCodeIsNullJump(v, pRight, regBase+nEq, addrNxt);
      if( zStartAff ){
        if( sqlite3CompareAffinity(pRight, zStartAff[nEq])==SQLITE_AFF_NONE){
          /* Since the comparison is to be performed with no conversions
          ** applied to the operands, set the affinity to apply to pRight to 
          ** SQLITE_AFF_NONE.  */
          zStartAff[nEq] = SQLITE_AFF_NONE;
        }
        if( sqlite3ExprNeedsNoAffinityChange(pRight, zStartAff[nEq]) ){
          zStartAff[nEq] = SQLITE_AFF_NONE;
        }
      }  
      nConstraint++;
      testcase( pRangeStart->wtFlags & TERM_VIRTUAL ); /* EV: R-30575-11662 */
    }else if( isMinQuery ){
      sqlite3VdbeAddOp2(v, OP_Null, 0, regBase+nEq);
      nConstraint++;
      startEq = 0;
      start_constraints = 1;
    }
    codeApplyAffinity(pParse, regBase, nConstraint, zStartAff);
    op = aStartOp[(start_constraints<<2) + (startEq<<1) + bRev];
    assert( op!=0 );
    testcase( op==OP_Rewind );
    testcase( op==OP_Last );
    testcase( op==OP_SeekGt );
    testcase( op==OP_SeekGe );
    testcase( op==OP_SeekLe );
    testcase( op==OP_SeekLt );
    sqlite3VdbeAddOp4Int(v, op, iIdxCur, addrNxt, regBase, nConstraint);

    /* Load the value for the inequality constraint at the end of the
    ** range (if any).
    */
    nConstraint = nEq;
    if( pRangeEnd ){
      Expr *pRight = pRangeEnd->pExpr->pRight;
      sqlite3ExprCacheRemove(pParse, regBase+nEq, 1);
      sqlite3ExprCode(pParse, pRight, regBase+nEq);
      sqlite3ExprCodeIsNullJump(v, pRight, regBase+nEq, addrNxt);
      if( zEndAff ){
        if( sqlite3CompareAffinity(pRight, zEndAff[nEq])==SQLITE_AFF_NONE){
          /* Since the comparison is to be performed with no conversions
          ** applied to the operands, set the affinity to apply to pRight to 
          ** SQLITE_AFF_NONE.  */
          zEndAff[nEq] = SQLITE_AFF_NONE;
        }
        if( sqlite3ExprNeedsNoAffinityChange(pRight, zEndAff[nEq]) ){
          zEndAff[nEq] = SQLITE_AFF_NONE;
        }
      }  
      codeApplyAffinity(pParse, regBase, nEq+1, zEndAff);
      nConstraint++;
      testcase( pRangeEnd->wtFlags & TERM_VIRTUAL ); /* EV: R-30575-11662 */
    }
    sqlite3DbFree(pParse->db, zStartAff);
    sqlite3DbFree(pParse->db, zEndAff);

    /* Top of the loop body */
    pLevel->p2 = sqlite3VdbeCurrentAddr(v);

    /* Check if the index cursor is past the end of the range. */
    op = aEndOp[(pRangeEnd || nEq) * (1 + bRev)];
    testcase( op==OP_Noop );
    testcase( op==OP_IdxGE );
    testcase( op==OP_IdxLT );
    if( op!=OP_Noop ){
      sqlite3VdbeAddOp4Int(v, op, iIdxCur, addrNxt, regBase, nConstraint);
      sqlite3VdbeChangeP5(v, endEq!=bRev ?1:0);
    }

    /* If there are inequality constraints, check that the value
    ** of the table column that the inequality contrains is not NULL.
    ** If it is, jump to the next iteration of the loop.
    */
    r1 = sqlite3GetTempReg(pParse);
    testcase( pLevel->plan.wsFlags & WHERE_BTM_LIMIT );
    testcase( pLevel->plan.wsFlags & WHERE_TOP_LIMIT );
    if( pLevel->plan.wsFlags & (WHERE_BTM_LIMIT|WHERE_TOP_LIMIT) ){
      sqlite3VdbeAddOp3(v, OP_Column, iIdxCur, nEq, r1);
      sqlite3VdbeAddOp2(v, OP_IsNull, r1, addrCont);
    }
    sqlite3ReleaseTempReg(pParse, r1);

    /* Seek the table cursor, if required */
    disableTerm(pLevel, pRangeStart);
    disableTerm(pLevel, pRangeEnd);
    if( !omitTable ){
      iRowidReg = iReleaseReg = sqlite3GetTempReg(pParse);
      sqlite3VdbeAddOp2(v, OP_IdxRowid, iIdxCur, iRowidReg);
      sqlite3ExprCacheStore(pParse, iCur, -1, iRowidReg);
      sqlite3VdbeAddOp2(v, OP_Seek, iCur, iRowidReg);  /* Deferred seek */
    }

    /* Record the instruction used to terminate the loop. Disable 
    ** WHERE clause terms made redundant by the index range scan.
    */
    pLevel->op = bRev ? OP_Prev : OP_Next;
    pLevel->p1 = iIdxCur;
  }else

#ifndef SQLITE_OMIT_OR_OPTIMIZATION
  if( pLevel->plan.wsFlags & WHERE_MULTI_OR ){
    /* Case 4:  Two or more separately indexed terms connected by OR
    **
    ** Example:
    **
    **   CREATE TABLE t1(a,b,c,d);
    **   CREATE INDEX i1 ON t1(a);
    **   CREATE INDEX i2 ON t1(b);
    **   CREATE INDEX i3 ON t1(c);
    **
    **   SELECT * FROM t1 WHERE a=5 OR b=7 OR (c=11 AND d=13)
    **
    ** In the example, there are three indexed terms connected by OR.
    ** The top of the loop looks like this:
    **
    **          Null       1                # Zero the rowset in reg 1
    **
    ** Then, for each indexed term, the following. The arguments to
    ** RowSetTest are such that the rowid of the current row is inserted
    ** into the RowSet. If it is already present, control skips the
    ** Gosub opcode and jumps straight to the code generated by WhereEnd().
    **
    **        sqlite3WhereBegin(<term>)
    **          RowSetTest                  # Insert rowid into rowset
    **          Gosub      2 A
    **        sqlite3WhereEnd()
    **
    ** Following the above, code to terminate the loop. Label A, the target
    ** of the Gosub above, jumps to the instruction right after the Goto.
    **
    **          Null       1                # Zero the rowset in reg 1
    **          Goto       B                # The loop is finished.
    **
    **       A: <loop body>                 # Return data, whatever.
    **
    **          Return     2                # Jump back to the Gosub
    **
    **       B: <after the loop>
    **
    */
    WhereClause *pOrWc;    /* The OR-clause broken out into subterms */
    WhereTerm *pFinal;     /* Final subterm within the OR-clause. */
    SrcList *pOrTab;       /* Shortened table list or OR-clause generation */

    int regReturn = ++pParse->nMem;           /* Register used with OP_Gosub */
    int regRowset = 0;                        /* Register for RowSet object */
    int regRowid = 0;                         /* Register holding rowid */
    int iLoopBody = sqlite3VdbeMakeLabel(v);  /* Start of loop body */
    int iRetInit;                             /* Address of regReturn init */
    int untestedTerms = 0;             /* Some terms not completely tested */
    int ii;
   
    pTerm = pLevel->plan.u.pTerm;
    assert( pTerm!=0 );
    assert( pTerm->eOperator==WO_OR );
    assert( (pTerm->wtFlags & TERM_ORINFO)!=0 );
    pOrWc = &pTerm->u.pOrInfo->wc;
    pFinal = &pOrWc->a[pOrWc->nTerm-1];
    pLevel->op = OP_Return;
    pLevel->p1 = regReturn;

    /* Set up a new SrcList ni pOrTab containing the table being scanned
    ** by this loop in the a[0] slot and all notReady tables in a[1..] slots.
    ** This becomes the SrcList in the recursive call to sqlite3WhereBegin().
    */
    if( pWInfo->nLevel>1 ){
      int nNotReady;                 /* The number of notReady tables */
      struct SrcList_item *origSrc;     /* Original list of tables */
      nNotReady = pWInfo->nLevel - iLevel - 1;
      pOrTab = sqlite3StackAllocRaw(pParse->db,
                            sizeof(*pOrTab)+ nNotReady*sizeof(pOrTab->a[0]));
      if( pOrTab==0 ) return notReady;
      pOrTab->nAlloc = (i16)(nNotReady + 1);
      pOrTab->nSrc = pOrTab->nAlloc;
      memcpy(pOrTab->a, pTabItem, sizeof(*pTabItem));
      origSrc = pWInfo->pTabList->a;
      for(k=1; k<=nNotReady; k++){
        memcpy(&pOrTab->a[k], &origSrc[pLevel[k].iFrom], sizeof(pOrTab->a[k]));
      }
    }else{
      pOrTab = pWInfo->pTabList;
    }

    /* Initialize the rowset register to contain NULL. An SQL NULL is 
    ** equivalent to an empty rowset.
    **
    ** Also initialize regReturn to contain the address of the instruction 
    ** immediately following the OP_Return at the bottom of the loop. This
    ** is required in a few obscure LEFT JOIN cases where control jumps
    ** over the top of the loop into the body of it. In this case the 
    ** correct response for the end-of-loop code (the OP_Return) is to 
    ** fall through to the next instruction, just as an OP_Next does if
    ** called on an uninitialized cursor.
    */
    if( (wctrlFlags & WHERE_DUPLICATES_OK)==0 ){
      regRowset = ++pParse->nMem;
      regRowid = ++pParse->nMem;
      sqlite3VdbeAddOp2(v, OP_Null, 0, regRowset);
    }
    iRetInit = sqlite3VdbeAddOp2(v, OP_Integer, 0, regReturn);

    for(ii=0; ii<pOrWc->nTerm; ii++){
      WhereTerm *pOrTerm = &pOrWc->a[ii];
      if( pOrTerm->leftCursor==iCur || pOrTerm->eOperator==WO_AND ){
        WhereInfo *pSubWInfo;          /* Info for single OR-term scan */
        /* Loop through table entries that match term pOrTerm. */
        pSubWInfo = sqlite3WhereBegin(pParse, pOrTab, pOrTerm->pExpr, 0,
                        WHERE_OMIT_OPEN | WHERE_OMIT_CLOSE |
                        WHERE_FORCE_TABLE | WHERE_ONETABLE_ONLY);
        if( pSubWInfo ){
          if( (wctrlFlags & WHERE_DUPLICATES_OK)==0 ){
            int iSet = ((ii==pOrWc->nTerm-1)?-1:ii);
            int r;
            r = sqlite3ExprCodeGetColumn(pParse, pTabItem->pTab, -1, iCur, 
                                         regRowid);
            sqlite3VdbeAddOp4Int(v, OP_RowSetTest, regRowset,
                                 sqlite3VdbeCurrentAddr(v)+2, r, iSet);
          }
          sqlite3VdbeAddOp2(v, OP_Gosub, regReturn, iLoopBody);

          /* The pSubWInfo->untestedTerms flag means that this OR term
          ** contained one or more AND term from a notReady table.  The
          ** terms from the notReady table could not be tested and will
          ** need to be tested later.
          */
          if( pSubWInfo->untestedTerms ) untestedTerms = 1;

          /* Finish the loop through table entries that match term pOrTerm. */
          sqlite3WhereEnd(pSubWInfo);
        }
      }
    }
    sqlite3VdbeChangeP1(v, iRetInit, sqlite3VdbeCurrentAddr(v));
    sqlite3VdbeAddOp2(v, OP_Goto, 0, pLevel->addrBrk);
    sqlite3VdbeResolveLabel(v, iLoopBody);

    if( pWInfo->nLevel>1 ) sqlite3StackFree(pParse->db, pOrTab);
    if( !untestedTerms ) disableTerm(pLevel, pTerm);
  }else
#endif /* SQLITE_OMIT_OR_OPTIMIZATION */

  {
    /* Case 5:  There is no usable index.  We must do a complete
    **          scan of the entire table.
    */
    static const u8 aStep[] = { OP_Next, OP_Prev };
    static const u8 aStart[] = { OP_Rewind, OP_Last };
    assert( bRev==0 || bRev==1 );
    assert( omitTable==0 );
    pLevel->op = aStep[bRev];
    pLevel->p1 = iCur;
    pLevel->p2 = 1 + sqlite3VdbeAddOp2(v, aStart[bRev], iCur, addrBrk);
    pLevel->p5 = SQLITE_STMTSTATUS_FULLSCAN_STEP;
  }
