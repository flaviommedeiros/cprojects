switch( pExpr->op ){
    case TK_AND: {
      testcase( jumpIfNull==0 );
      sqlite3ExprIfFalse(pParse, pExpr->pLeft, dest, jumpIfNull);
      sqlite3ExprIfFalse(pParse, pExpr->pRight, dest, jumpIfNull);
      break;
    }
    case TK_OR: {
      int d2 = sqlite3VdbeMakeLabel(v);
      testcase( jumpIfNull==0 );
      sqlite3ExprCachePush(pParse);
      sqlite3ExprIfTrue(pParse, pExpr->pLeft, d2, jumpIfNull^SQLITE_JUMPIFNULL);
      sqlite3ExprIfFalse(pParse, pExpr->pRight, dest, jumpIfNull);
      sqlite3VdbeResolveLabel(v, d2);
      sqlite3ExprCachePop(pParse, 1);
      break;
    }
    case TK_NOT: {
      testcase( jumpIfNull==0 );
      sqlite3ExprIfTrue(pParse, pExpr->pLeft, dest, jumpIfNull);
      break;
    }
    case TK_LT:
    case TK_LE:
    case TK_GT:
    case TK_GE:
    case TK_NE:
    case TK_EQ: {
      testcase( op==TK_LT );
      testcase( op==TK_LE );
      testcase( op==TK_GT );
      testcase( op==TK_GE );
      testcase( op==TK_EQ );
      testcase( op==TK_NE );
      testcase( jumpIfNull==0 );
      r1 = sqlite3ExprCodeTemp(pParse, pExpr->pLeft, &regFree1);
      r2 = sqlite3ExprCodeTemp(pParse, pExpr->pRight, &regFree2);
      codeCompare(pParse, pExpr->pLeft, pExpr->pRight, op,
                  r1, r2, dest, jumpIfNull);
      testcase( regFree1==0 );
      testcase( regFree2==0 );
      break;
    }
    case TK_IS:
    case TK_ISNOT: {
      testcase( pExpr->op==TK_IS );
      testcase( pExpr->op==TK_ISNOT );
      r1 = sqlite3ExprCodeTemp(pParse, pExpr->pLeft, &regFree1);
      r2 = sqlite3ExprCodeTemp(pParse, pExpr->pRight, &regFree2);
      op = (pExpr->op==TK_IS) ? TK_NE : TK_EQ;
      codeCompare(pParse, pExpr->pLeft, pExpr->pRight, op,
                  r1, r2, dest, SQLITE_NULLEQ);
      testcase( regFree1==0 );
      testcase( regFree2==0 );
      break;
    }
    case TK_ISNULL:
    case TK_NOTNULL: {
      testcase( op==TK_ISNULL );
      testcase( op==TK_NOTNULL );
      r1 = sqlite3ExprCodeTemp(pParse, pExpr->pLeft, &regFree1);
      sqlite3VdbeAddOp2(v, op, r1, dest);
      testcase( regFree1==0 );
      break;
    }
    case TK_BETWEEN: {
      testcase( jumpIfNull==0 );
      exprCodeBetween(pParse, pExpr, dest, 0, jumpIfNull);
      break;
    }
#ifndef SQLITE_OMIT_SUBQUERY
    case TK_IN: {
      if( jumpIfNull ){
        sqlite3ExprCodeIN(pParse, pExpr, dest, dest);
      }else{
        int destIfNull = sqlite3VdbeMakeLabel(v);
        sqlite3ExprCodeIN(pParse, pExpr, dest, destIfNull);
        sqlite3VdbeResolveLabel(v, destIfNull);
      }
      break;
    }
#endif
    default: {
      r1 = sqlite3ExprCodeTemp(pParse, pExpr, &regFree1);
      sqlite3VdbeAddOp3(v, OP_IfNot, r1, dest, jumpIfNull!=0);
      testcase( regFree1==0 );
      testcase( jumpIfNull==0 );
      break;
    }
  }
