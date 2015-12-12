switch( op ){
    case TK_AGG_COLUMN: {
      AggInfo *pAggInfo = pExpr->pAggInfo;
      struct AggInfo_col *pCol = &pAggInfo->aCol[pExpr->iAgg];
      if( !pAggInfo->directMode ){
        assert( pCol->iMem>0 );
        inReg = pCol->iMem;
        break;
      }else if( pAggInfo->useSortingIdx ){
        sqlite3VdbeAddOp3(v, OP_Column, pAggInfo->sortingIdxPTab,
                              pCol->iSorterColumn, target);
        break;
      }
      /* Otherwise, fall thru into the TK_COLUMN case */
    }
    case TK_COLUMN: {
      int iTab = pExpr->iTable;
      if( iTab<0 ){
        if( pParse->ckBase>0 ){
          /* Generating CHECK constraints or inserting into partial index */
          inReg = pExpr->iColumn + pParse->ckBase;
          break;
        }else{
          /* Deleting from a partial index */
          iTab = pParse->iPartIdxTab;
        }
      }
      inReg = sqlite3ExprCodeGetColumn(pParse, pExpr->pTab,
                               pExpr->iColumn, iTab, target,
                               pExpr->op2);
      break;
    }
    case TK_INTEGER: {
      codeInteger(pParse, pExpr, 0, target);
      break;
    }
#ifndef SQLITE_OMIT_FLOATING_POINT
    case TK_FLOAT: {
      assert( !ExprHasProperty(pExpr, EP_IntValue) );
      codeReal(v, pExpr->u.zToken, 0, target);
      break;
    }
#endif
    case TK_STRING: {
      assert( !ExprHasProperty(pExpr, EP_IntValue) );
      sqlite3VdbeAddOp4(v, OP_String8, 0, target, 0, pExpr->u.zToken, 0);
      break;
    }
    case TK_NULL: {
      sqlite3VdbeAddOp2(v, OP_Null, 0, target);
      break;
    }
#ifndef SQLITE_OMIT_BLOB_LITERAL
    case TK_BLOB: {
      int n;
      const char *z;
      char *zBlob;
      assert( !ExprHasProperty(pExpr, EP_IntValue) );
      assert( pExpr->u.zToken[0]=='x' || pExpr->u.zToken[0]=='X' );
      assert( pExpr->u.zToken[1]=='\'' );
      z = &pExpr->u.zToken[2];
      n = sqlite3Strlen30(z) - 1;
      assert( z[n]=='\'' );
      zBlob = sqlite3HexToBlob(sqlite3VdbeDb(v), z, n);
      sqlite3VdbeAddOp4(v, OP_Blob, n/2, target, 0, zBlob, P4_DYNAMIC);
      break;
    }
#endif
    case TK_VARIABLE: {
      assert( !ExprHasProperty(pExpr, EP_IntValue) );
      assert( pExpr->u.zToken!=0 );
      assert( pExpr->u.zToken[0]!=0 );
      sqlite3VdbeAddOp2(v, OP_Variable, pExpr->iColumn, target);
      if( pExpr->u.zToken[1]!=0 ){
        assert( pExpr->u.zToken[0]=='?' 
             || strcmp(pExpr->u.zToken, pParse->azVar[pExpr->iColumn-1])==0 );
        sqlite3VdbeChangeP4(v, -1, pParse->azVar[pExpr->iColumn-1], P4_STATIC);
      }
      break;
    }
    case TK_REGISTER: {
      inReg = pExpr->iTable;
      break;
    }
    case TK_AS: {
      inReg = sqlite3ExprCodeTarget(pParse, pExpr->pLeft, target);
      break;
    }
#ifndef SQLITE_OMIT_CAST
    case TK_CAST: {
      /* Expressions of the form:   CAST(pLeft AS token) */
      int aff, to_op;
      inReg = sqlite3ExprCodeTarget(pParse, pExpr->pLeft, target);
      assert( !ExprHasProperty(pExpr, EP_IntValue) );
      aff = sqlite3AffinityType(pExpr->u.zToken, 0);
      to_op = aff - SQLITE_AFF_TEXT + OP_ToText;
      assert( to_op==OP_ToText    || aff!=SQLITE_AFF_TEXT    );
      assert( to_op==OP_ToBlob    || aff!=SQLITE_AFF_NONE    );
      assert( to_op==OP_ToNumeric || aff!=SQLITE_AFF_NUMERIC );
      assert( to_op==OP_ToInt     || aff!=SQLITE_AFF_INTEGER );
      assert( to_op==OP_ToReal    || aff!=SQLITE_AFF_REAL    );
      testcase( to_op==OP_ToText );
      testcase( to_op==OP_ToBlob );
      testcase( to_op==OP_ToNumeric );
      testcase( to_op==OP_ToInt );
      testcase( to_op==OP_ToReal );
      if( inReg!=target ){
        sqlite3VdbeAddOp2(v, OP_SCopy, inReg, target);
        inReg = target;
      }
      sqlite3VdbeAddOp1(v, to_op, inReg);
      testcase( usedAsColumnCache(pParse, inReg, inReg) );
      sqlite3ExprCacheAffinityChange(pParse, inReg, 1);
      break;
    }
#endif /* SQLITE_OMIT_CAST */
    case TK_LT:
    case TK_LE:
    case TK_GT:
    case TK_GE:
    case TK_NE:
    case TK_EQ: {
      assert( TK_LT==OP_Lt );
      assert( TK_LE==OP_Le );
      assert( TK_GT==OP_Gt );
      assert( TK_GE==OP_Ge );
      assert( TK_EQ==OP_Eq );
      assert( TK_NE==OP_Ne );
      testcase( op==TK_LT );
      testcase( op==TK_LE );
      testcase( op==TK_GT );
      testcase( op==TK_GE );
      testcase( op==TK_EQ );
      testcase( op==TK_NE );
      r1 = sqlite3ExprCodeTemp(pParse, pExpr->pLeft, &regFree1);
      r2 = sqlite3ExprCodeTemp(pParse, pExpr->pRight, &regFree2);
      codeCompare(pParse, pExpr->pLeft, pExpr->pRight, op,
                  r1, r2, inReg, SQLITE_STOREP2);
      testcase( regFree1==0 );
      testcase( regFree2==0 );
      break;
    }
    case TK_IS:
    case TK_ISNOT: {
      testcase( op==TK_IS );
      testcase( op==TK_ISNOT );
      r1 = sqlite3ExprCodeTemp(pParse, pExpr->pLeft, &regFree1);
      r2 = sqlite3ExprCodeTemp(pParse, pExpr->pRight, &regFree2);
      op = (op==TK_IS) ? TK_EQ : TK_NE;
      codeCompare(pParse, pExpr->pLeft, pExpr->pRight, op,
                  r1, r2, inReg, SQLITE_STOREP2 | SQLITE_NULLEQ);
      testcase( regFree1==0 );
      testcase( regFree2==0 );
      break;
    }
    case TK_AND:
    case TK_OR:
    case TK_PLUS:
    case TK_STAR:
    case TK_MINUS:
    case TK_REM:
    case TK_BITAND:
    case TK_BITOR:
    case TK_SLASH:
    case TK_LSHIFT:
    case TK_RSHIFT: 
    case TK_CONCAT: {
      assert( TK_AND==OP_And );
      assert( TK_OR==OP_Or );
      assert( TK_PLUS==OP_Add );
      assert( TK_MINUS==OP_Subtract );
      assert( TK_REM==OP_Remainder );
      assert( TK_BITAND==OP_BitAnd );
      assert( TK_BITOR==OP_BitOr );
      assert( TK_SLASH==OP_Divide );
      assert( TK_LSHIFT==OP_ShiftLeft );
      assert( TK_RSHIFT==OP_ShiftRight );
      assert( TK_CONCAT==OP_Concat );
      testcase( op==TK_AND );
      testcase( op==TK_OR );
      testcase( op==TK_PLUS );
      testcase( op==TK_MINUS );
      testcase( op==TK_REM );
      testcase( op==TK_BITAND );
      testcase( op==TK_BITOR );
      testcase( op==TK_SLASH );
      testcase( op==TK_LSHIFT );
      testcase( op==TK_RSHIFT );
      testcase( op==TK_CONCAT );
      r1 = sqlite3ExprCodeTemp(pParse, pExpr->pLeft, &regFree1);
      r2 = sqlite3ExprCodeTemp(pParse, pExpr->pRight, &regFree2);
      sqlite3VdbeAddOp3(v, op, r2, r1, target);
      testcase( regFree1==0 );
      testcase( regFree2==0 );
      break;
    }
    case TK_UMINUS: {
      Expr *pLeft = pExpr->pLeft;
      assert( pLeft );
      if( pLeft->op==TK_INTEGER ){
        codeInteger(pParse, pLeft, 1, target);
#ifndef SQLITE_OMIT_FLOATING_POINT
      }else if( pLeft->op==TK_FLOAT ){
        assert( !ExprHasProperty(pExpr, EP_IntValue) );
        codeReal(v, pLeft->u.zToken, 1, target);
#endif
      }else{
        tempX.op = TK_INTEGER;
        tempX.flags = EP_IntValue|EP_TokenOnly;
        tempX.u.iValue = 0;
        r1 = sqlite3ExprCodeTemp(pParse, &tempX, &regFree1);
        r2 = sqlite3ExprCodeTemp(pParse, pExpr->pLeft, &regFree2);
        sqlite3VdbeAddOp3(v, OP_Subtract, r2, r1, target);
        testcase( regFree2==0 );
      }
      inReg = target;
      break;
    }
    case TK_BITNOT:
    case TK_NOT: {
      assert( TK_BITNOT==OP_BitNot );
      assert( TK_NOT==OP_Not );
      testcase( op==TK_BITNOT );
      testcase( op==TK_NOT );
      r1 = sqlite3ExprCodeTemp(pParse, pExpr->pLeft, &regFree1);
      testcase( regFree1==0 );
      inReg = target;
      sqlite3VdbeAddOp2(v, op, r1, inReg);
      break;
    }
    case TK_ISNULL:
    case TK_NOTNULL: {
      int addr;
      assert( TK_ISNULL==OP_IsNull );
      assert( TK_NOTNULL==OP_NotNull );
      testcase( op==TK_ISNULL );
      testcase( op==TK_NOTNULL );
      sqlite3VdbeAddOp2(v, OP_Integer, 1, target);
      r1 = sqlite3ExprCodeTemp(pParse, pExpr->pLeft, &regFree1);
      testcase( regFree1==0 );
      addr = sqlite3VdbeAddOp1(v, op, r1);
      sqlite3VdbeAddOp2(v, OP_AddImm, target, -1);
      sqlite3VdbeJumpHere(v, addr);
      break;
    }
    case TK_AGG_FUNCTION: {
      AggInfo *pInfo = pExpr->pAggInfo;
      if( pInfo==0 ){
        assert( !ExprHasProperty(pExpr, EP_IntValue) );
        sqlite3ErrorMsg(pParse, "misuse of aggregate: %s()", pExpr->u.zToken);
      }else{
        inReg = pInfo->aFunc[pExpr->iAgg].iMem;
      }
      break;
    }
    case TK_FUNCTION: {
      ExprList *pFarg;       /* List of function arguments */
      int nFarg;             /* Number of function arguments */
      FuncDef *pDef;         /* The function definition object */
      int nId;               /* Length of the function name in bytes */
      const char *zId;       /* The function name */
      int constMask = 0;     /* Mask of function arguments that are constant */
      int i;                 /* Loop counter */
      u8 enc = ENC(db);      /* The text encoding used by this database */
      CollSeq *pColl = 0;    /* A collating sequence */

      assert( !ExprHasProperty(pExpr, EP_xIsSelect) );
      if( ExprHasProperty(pExpr, EP_TokenOnly) ){
        pFarg = 0;
      }else{
        pFarg = pExpr->x.pList;
      }
      nFarg = pFarg ? pFarg->nExpr : 0;
      assert( !ExprHasProperty(pExpr, EP_IntValue) );
      zId = pExpr->u.zToken;
      nId = sqlite3Strlen30(zId);
      pDef = sqlite3FindFunction(db, zId, nId, nFarg, enc, 0);
      if( pDef==0 ){
        sqlite3ErrorMsg(pParse, "unknown function: %.*s()", nId, zId);
        break;
      }

      /* Attempt a direct implementation of the built-in COALESCE() and
      ** IFNULL() functions.  This avoids unnecessary evalation of
      ** arguments past the first non-NULL argument.
      */
      if( pDef->funcFlags & SQLITE_FUNC_COALESCE ){
        int endCoalesce = sqlite3VdbeMakeLabel(v);
        assert( nFarg>=2 );
        sqlite3ExprCode(pParse, pFarg->a[0].pExpr, target);
        for(i=1; i<nFarg; i++){
          sqlite3VdbeAddOp2(v, OP_NotNull, target, endCoalesce);
          sqlite3ExprCacheRemove(pParse, target, 1);
          sqlite3ExprCachePush(pParse);
          sqlite3ExprCode(pParse, pFarg->a[i].pExpr, target);
          sqlite3ExprCachePop(pParse, 1);
        }
        sqlite3VdbeResolveLabel(v, endCoalesce);
        break;
      }

      /* The UNLIKELY() function is a no-op.  The result is the value
      ** of the first argument.
      */
      if( pDef->funcFlags & SQLITE_FUNC_UNLIKELY ){
        assert( nFarg>=1 );
        sqlite3ExprCode(pParse, pFarg->a[0].pExpr, target);
        break;
      }

      for(i=0; i<nFarg; i++){
        if( i<32 && sqlite3ExprIsConstant(pFarg->a[i].pExpr) ){
          constMask |= (1<<i);
        }
        if( (pDef->funcFlags & SQLITE_FUNC_NEEDCOLL)!=0 && !pColl ){
          pColl = sqlite3ExprCollSeq(pParse, pFarg->a[i].pExpr);
        }
      }
      if( pFarg ){
        if( constMask ){
          r1 = pParse->nMem+1;
          pParse->nMem += nFarg;
        }else{
          r1 = sqlite3GetTempRange(pParse, nFarg);
        }

        /* For length() and typeof() functions with a column argument,
        ** set the P5 parameter to the OP_Column opcode to OPFLAG_LENGTHARG
        ** or OPFLAG_TYPEOFARG respectively, to avoid unnecessary data
        ** loading.
        */
        if( (pDef->funcFlags & (SQLITE_FUNC_LENGTH|SQLITE_FUNC_TYPEOF))!=0 ){
          u8 exprOp;
          assert( nFarg==1 );
          assert( pFarg->a[0].pExpr!=0 );
          exprOp = pFarg->a[0].pExpr->op;
          if( exprOp==TK_COLUMN || exprOp==TK_AGG_COLUMN ){
            assert( SQLITE_FUNC_LENGTH==OPFLAG_LENGTHARG );
            assert( SQLITE_FUNC_TYPEOF==OPFLAG_TYPEOFARG );
            testcase( pDef->funcFlags & OPFLAG_LENGTHARG );
            pFarg->a[0].pExpr->op2 = 
                  pDef->funcFlags & (OPFLAG_LENGTHARG|OPFLAG_TYPEOFARG);
          }
        }

        sqlite3ExprCachePush(pParse);     /* Ticket 2ea2425d34be */
        sqlite3ExprCodeExprList(pParse, pFarg, r1, 
                                SQLITE_ECEL_DUP|SQLITE_ECEL_FACTOR);
        sqlite3ExprCachePop(pParse, 1);   /* Ticket 2ea2425d34be */
      }else{
        r1 = 0;
      }
#ifndef SQLITE_OMIT_VIRTUALTABLE
      /* Possibly overload the function if the first argument is
      ** a virtual table column.
      **
      ** For infix functions (LIKE, GLOB, REGEXP, and MATCH) use the
      ** second argument, not the first, as the argument to test to
      ** see if it is a column in a virtual table.  This is done because
      ** the left operand of infix functions (the operand we want to
      ** control overloading) ends up as the second argument to the
      ** function.  The expression "A glob B" is equivalent to 
      ** "glob(B,A).  We want to use the A in "A glob B" to test
      ** for function overloading.  But we use the B term in "glob(B,A)".
      */
      if( nFarg>=2 && (pExpr->flags & EP_InfixFunc) ){
        pDef = sqlite3VtabOverloadFunction(db, pDef, nFarg, pFarg->a[1].pExpr);
      }else if( nFarg>0 ){
        pDef = sqlite3VtabOverloadFunction(db, pDef, nFarg, pFarg->a[0].pExpr);
      }
#endif
      if( pDef->funcFlags & SQLITE_FUNC_NEEDCOLL ){
        if( !pColl ) pColl = db->pDfltColl; 
        sqlite3VdbeAddOp4(v, OP_CollSeq, 0, 0, 0, (char *)pColl, P4_COLLSEQ);
      }
      sqlite3VdbeAddOp4(v, OP_Function, constMask, r1, target,
                        (char*)pDef, P4_FUNCDEF);
      sqlite3VdbeChangeP5(v, (u8)nFarg);
      if( nFarg && constMask==0 ){
        sqlite3ReleaseTempRange(pParse, r1, nFarg);
      }
      break;
    }
#ifndef SQLITE_OMIT_SUBQUERY
    case TK_EXISTS:
    case TK_SELECT: {
      testcase( op==TK_EXISTS );
      testcase( op==TK_SELECT );
      inReg = sqlite3CodeSubselect(pParse, pExpr, 0, 0);
      break;
    }
    case TK_IN: {
      int destIfFalse = sqlite3VdbeMakeLabel(v);
      int destIfNull = sqlite3VdbeMakeLabel(v);
      sqlite3VdbeAddOp2(v, OP_Null, 0, target);
      sqlite3ExprCodeIN(pParse, pExpr, destIfFalse, destIfNull);
      sqlite3VdbeAddOp2(v, OP_Integer, 1, target);
      sqlite3VdbeResolveLabel(v, destIfFalse);
      sqlite3VdbeAddOp2(v, OP_AddImm, target, 0);
      sqlite3VdbeResolveLabel(v, destIfNull);
      break;
    }
#endif /* SQLITE_OMIT_SUBQUERY */


    /*
    **    x BETWEEN y AND z
    **
    ** This is equivalent to
    **
    **    x>=y AND x<=z
    **
    ** X is stored in pExpr->pLeft.
    ** Y is stored in pExpr->pList->a[0].pExpr.
    ** Z is stored in pExpr->pList->a[1].pExpr.
    */
    case TK_BETWEEN: {
      Expr *pLeft = pExpr->pLeft;
      struct ExprList_item *pLItem = pExpr->x.pList->a;
      Expr *pRight = pLItem->pExpr;

      r1 = sqlite3ExprCodeTemp(pParse, pLeft, &regFree1);
      r2 = sqlite3ExprCodeTemp(pParse, pRight, &regFree2);
      testcase( regFree1==0 );
      testcase( regFree2==0 );
      r3 = sqlite3GetTempReg(pParse);
      r4 = sqlite3GetTempReg(pParse);
      codeCompare(pParse, pLeft, pRight, OP_Ge,
                  r1, r2, r3, SQLITE_STOREP2);
      pLItem++;
      pRight = pLItem->pExpr;
      sqlite3ReleaseTempReg(pParse, regFree2);
      r2 = sqlite3ExprCodeTemp(pParse, pRight, &regFree2);
      testcase( regFree2==0 );
      codeCompare(pParse, pLeft, pRight, OP_Le, r1, r2, r4, SQLITE_STOREP2);
      sqlite3VdbeAddOp3(v, OP_And, r3, r4, target);
      sqlite3ReleaseTempReg(pParse, r3);
      sqlite3ReleaseTempReg(pParse, r4);
      break;
    }
    case TK_COLLATE: 
    case TK_UPLUS: {
      inReg = sqlite3ExprCodeTarget(pParse, pExpr->pLeft, target);
      break;
    }

    case TK_TRIGGER: {
      /* If the opcode is TK_TRIGGER, then the expression is a reference
      ** to a column in the new.* or old.* pseudo-tables available to
      ** trigger programs. In this case Expr.iTable is set to 1 for the
      ** new.* pseudo-table, or 0 for the old.* pseudo-table. Expr.iColumn
      ** is set to the column of the pseudo-table to read, or to -1 to
      ** read the rowid field.
      **
      ** The expression is implemented using an OP_Param opcode. The p1
      ** parameter is set to 0 for an old.rowid reference, or to (i+1)
      ** to reference another column of the old.* pseudo-table, where 
      ** i is the index of the column. For a new.rowid reference, p1 is
      ** set to (n+1), where n is the number of columns in each pseudo-table.
      ** For a reference to any other column in the new.* pseudo-table, p1
      ** is set to (n+2+i), where n and i are as defined previously. For
      ** example, if the table on which triggers are being fired is
      ** declared as:
      **
      **   CREATE TABLE t1(a, b);
      **
      ** Then p1 is interpreted as follows:
      **
      **   p1==0   ->    old.rowid     p1==3   ->    new.rowid
      **   p1==1   ->    old.a         p1==4   ->    new.a
      **   p1==2   ->    old.b         p1==5   ->    new.b       
      */
      Table *pTab = pExpr->pTab;
      int p1 = pExpr->iTable * (pTab->nCol+1) + 1 + pExpr->iColumn;

      assert( pExpr->iTable==0 || pExpr->iTable==1 );
      assert( pExpr->iColumn>=-1 && pExpr->iColumn<pTab->nCol );
      assert( pTab->iPKey<0 || pExpr->iColumn!=pTab->iPKey );
      assert( p1>=0 && p1<(pTab->nCol*2+2) );

      sqlite3VdbeAddOp2(v, OP_Param, p1, target);
      VdbeComment((v, "%s.%s -> $%d",
        (pExpr->iTable ? "new" : "old"),
        (pExpr->iColumn<0 ? "rowid" : pExpr->pTab->aCol[pExpr->iColumn].zName),
        target
      ));

#ifndef SQLITE_OMIT_FLOATING_POINT
      /* If the column has REAL affinity, it may currently be stored as an
      ** integer. Use OP_RealAffinity to make sure it is really real.  */
      if( pExpr->iColumn>=0 
       && pTab->aCol[pExpr->iColumn].affinity==SQLITE_AFF_REAL
      ){
        sqlite3VdbeAddOp1(v, OP_RealAffinity, target);
      }
#endif
      break;
    }


    /*
    ** Form A:
    **   CASE x WHEN e1 THEN r1 WHEN e2 THEN r2 ... WHEN eN THEN rN ELSE y END
    **
    ** Form B:
    **   CASE WHEN e1 THEN r1 WHEN e2 THEN r2 ... WHEN eN THEN rN ELSE y END
    **
    ** Form A is can be transformed into the equivalent form B as follows:
    **   CASE WHEN x=e1 THEN r1 WHEN x=e2 THEN r2 ...
    **        WHEN x=eN THEN rN ELSE y END
    **
    ** X (if it exists) is in pExpr->pLeft.
    ** Y is in the last element of pExpr->x.pList if pExpr->x.pList->nExpr is
    ** odd.  The Y is also optional.  If the number of elements in x.pList
    ** is even, then Y is omitted and the "otherwise" result is NULL.
    ** Ei is in pExpr->pList->a[i*2] and Ri is pExpr->pList->a[i*2+1].
    **
    ** The result of the expression is the Ri for the first matching Ei,
    ** or if there is no matching Ei, the ELSE term Y, or if there is
    ** no ELSE term, NULL.
    */
    default: assert( op==TK_CASE ); {
      int endLabel;                     /* GOTO label for end of CASE stmt */
      int nextCase;                     /* GOTO label for next WHEN clause */
      int nExpr;                        /* 2x number of WHEN terms */
      int i;                            /* Loop counter */
      ExprList *pEList;                 /* List of WHEN terms */
      struct ExprList_item *aListelem;  /* Array of WHEN terms */
      Expr opCompare;                   /* The X==Ei expression */
      Expr *pX;                         /* The X expression */
      Expr *pTest = 0;                  /* X==Ei (form A) or just Ei (form B) */
      VVA_ONLY( int iCacheLevel = pParse->iCacheLevel; )

      assert( !ExprHasProperty(pExpr, EP_xIsSelect) && pExpr->x.pList );
      assert(pExpr->x.pList->nExpr > 0);
      pEList = pExpr->x.pList;
      aListelem = pEList->a;
      nExpr = pEList->nExpr;
      endLabel = sqlite3VdbeMakeLabel(v);
      if( (pX = pExpr->pLeft)!=0 ){
        tempX = *pX;
        testcase( pX->op==TK_COLUMN );
        exprToRegister(&tempX, sqlite3ExprCodeTemp(pParse, pX, &regFree1));
        testcase( regFree1==0 );
        opCompare.op = TK_EQ;
        opCompare.pLeft = &tempX;
        pTest = &opCompare;
        /* Ticket b351d95f9cd5ef17e9d9dbae18f5ca8611190001:
        ** The value in regFree1 might get SCopy-ed into the file result.
        ** So make sure that the regFree1 register is not reused for other
        ** purposes and possibly overwritten.  */
        regFree1 = 0;
      }
      for(i=0; i<nExpr-1; i=i+2){
        sqlite3ExprCachePush(pParse);
        if( pX ){
          assert( pTest!=0 );
          opCompare.pRight = aListelem[i].pExpr;
        }else{
          pTest = aListelem[i].pExpr;
        }
        nextCase = sqlite3VdbeMakeLabel(v);
        testcase( pTest->op==TK_COLUMN );
        sqlite3ExprIfFalse(pParse, pTest, nextCase, SQLITE_JUMPIFNULL);
        testcase( aListelem[i+1].pExpr->op==TK_COLUMN );
        sqlite3ExprCode(pParse, aListelem[i+1].pExpr, target);
        sqlite3VdbeAddOp2(v, OP_Goto, 0, endLabel);
        sqlite3ExprCachePop(pParse, 1);
        sqlite3VdbeResolveLabel(v, nextCase);
      }
      if( (nExpr&1)!=0 ){
        sqlite3ExprCachePush(pParse);
        sqlite3ExprCode(pParse, pEList->a[nExpr-1].pExpr, target);
        sqlite3ExprCachePop(pParse, 1);
      }else{
        sqlite3VdbeAddOp2(v, OP_Null, 0, target);
      }
      assert( db->mallocFailed || pParse->nErr>0 
           || pParse->iCacheLevel==iCacheLevel );
      sqlite3VdbeResolveLabel(v, endLabel);
      break;
    }
#ifndef SQLITE_OMIT_TRIGGER
    case TK_RAISE: {
      assert( pExpr->affinity==OE_Rollback 
           || pExpr->affinity==OE_Abort
           || pExpr->affinity==OE_Fail
           || pExpr->affinity==OE_Ignore
      );
      if( !pParse->pTriggerTab ){
        sqlite3ErrorMsg(pParse,
                       "RAISE() may only be used within a trigger-program");
        return 0;
      }
      if( pExpr->affinity==OE_Abort ){
        sqlite3MayAbort(pParse);
      }
      assert( !ExprHasProperty(pExpr, EP_IntValue) );
      if( pExpr->affinity==OE_Ignore ){
        sqlite3VdbeAddOp4(
            v, OP_Halt, SQLITE_OK, OE_Ignore, 0, pExpr->u.zToken,0);
      }else{
        sqlite3HaltConstraint(pParse, SQLITE_CONSTRAINT_TRIGGER,
                              pExpr->affinity, pExpr->u.zToken, 0, 0);
      }

      break;
    }
#endif
  }
