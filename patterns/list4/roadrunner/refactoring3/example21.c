switch( op ){
    case TK_AGG_COLUMN: {
      sqlite3ExplainPrintf(pOut, "AGG{%d:%d}",
            pExpr->iTable, pExpr->iColumn);
      break;
    }
    case TK_COLUMN: {
      if( pExpr->iTable<0 ){
        /* This only happens when coding check constraints */
        sqlite3ExplainPrintf(pOut, "COLUMN(%d)", pExpr->iColumn);
      }else{
        sqlite3ExplainPrintf(pOut, "{%d:%d}",
                             pExpr->iTable, pExpr->iColumn);
      }
      break;
    }
    case TK_INTEGER: {
      if( pExpr->flags & EP_IntValue ){
        sqlite3ExplainPrintf(pOut, "%d", pExpr->u.iValue);
      }else{
        sqlite3ExplainPrintf(pOut, "%s", pExpr->u.zToken);
      }
      break;
    }
#ifndef SQLITE_OMIT_FLOATING_POINT
    case TK_FLOAT: {
      sqlite3ExplainPrintf(pOut,"%s", pExpr->u.zToken);
      break;
    }
#endif
    case TK_STRING: {
      sqlite3ExplainPrintf(pOut,"%Q", pExpr->u.zToken);
      break;
    }
    case TK_NULL: {
      sqlite3ExplainPrintf(pOut,"NULL");
      break;
    }
#ifndef SQLITE_OMIT_BLOB_LITERAL
    case TK_BLOB: {
      sqlite3ExplainPrintf(pOut,"%s", pExpr->u.zToken);
      break;
    }
#endif
    case TK_VARIABLE: {
      sqlite3ExplainPrintf(pOut,"VARIABLE(%s,%d)",
                           pExpr->u.zToken, pExpr->iColumn);
      break;
    }
    case TK_REGISTER: {
      sqlite3ExplainPrintf(pOut,"REGISTER(%d)", pExpr->iTable);
      break;
    }
    case TK_AS: {
      sqlite3ExplainExpr(pOut, pExpr->pLeft);
      break;
    }
#ifndef SQLITE_OMIT_CAST
    case TK_CAST: {
      /* Expressions of the form:   CAST(pLeft AS token) */
      const char *zAff = "unk";
      switch( sqlite3AffinityType(pExpr->u.zToken) ){
        case SQLITE_AFF_TEXT:    zAff = "TEXT";     break;
        case SQLITE_AFF_NONE:    zAff = "NONE";     break;
        case SQLITE_AFF_NUMERIC: zAff = "NUMERIC";  break;
        case SQLITE_AFF_INTEGER: zAff = "INTEGER";  break;
        case SQLITE_AFF_REAL:    zAff = "REAL";     break;
      }
      sqlite3ExplainPrintf(pOut, "CAST-%s(", zAff);
      sqlite3ExplainExpr(pOut, pExpr->pLeft);
      sqlite3ExplainPrintf(pOut, ")");
      break;
    }
#endif /* SQLITE_OMIT_CAST */
    case TK_LT:      zBinOp = "LT";     break;
    case TK_LE:      zBinOp = "LE";     break;
    case TK_GT:      zBinOp = "GT";     break;
    case TK_GE:      zBinOp = "GE";     break;
    case TK_NE:      zBinOp = "NE";     break;
    case TK_EQ:      zBinOp = "EQ";     break;
    case TK_IS:      zBinOp = "IS";     break;
    case TK_ISNOT:   zBinOp = "ISNOT";  break;
    case TK_AND:     zBinOp = "AND";    break;
    case TK_OR:      zBinOp = "OR";     break;
    case TK_PLUS:    zBinOp = "ADD";    break;
    case TK_STAR:    zBinOp = "MUL";    break;
    case TK_MINUS:   zBinOp = "SUB";    break;
    case TK_REM:     zBinOp = "REM";    break;
    case TK_BITAND:  zBinOp = "BITAND"; break;
    case TK_BITOR:   zBinOp = "BITOR";  break;
    case TK_SLASH:   zBinOp = "DIV";    break;
    case TK_LSHIFT:  zBinOp = "LSHIFT"; break;
    case TK_RSHIFT:  zBinOp = "RSHIFT"; break;
    case TK_CONCAT:  zBinOp = "CONCAT"; break;

    case TK_UMINUS:  zUniOp = "UMINUS"; break;
    case TK_UPLUS:   zUniOp = "UPLUS";  break;
    case TK_BITNOT:  zUniOp = "BITNOT"; break;
    case TK_NOT:     zUniOp = "NOT";    break;
    case TK_ISNULL:  zUniOp = "ISNULL"; break;
    case TK_NOTNULL: zUniOp = "NOTNULL"; break;

    case TK_COLLATE: {
      sqlite3ExplainExpr(pOut, pExpr->pLeft);
      sqlite3ExplainPrintf(pOut,".COLLATE(%s)",pExpr->u.zToken);
      break;
    }

    case TK_AGG_FUNCTION:
    case TK_CONST_FUNC:
    case TK_FUNCTION: {
      ExprList *pFarg;       /* List of function arguments */
      if( ExprHasAnyProperty(pExpr, EP_TokenOnly) ){
        pFarg = 0;
      }else{
        pFarg = pExpr->x.pList;
      }
      if( op==TK_AGG_FUNCTION ){
        sqlite3ExplainPrintf(pOut, "AGG_FUNCTION%d:%s(",
                             pExpr->op2, pExpr->u.zToken);
      }else{
        sqlite3ExplainPrintf(pOut, "FUNCTION:%s(", pExpr->u.zToken);
      }
      if( pFarg ){
        sqlite3ExplainExprList(pOut, pFarg);
      }
      sqlite3ExplainPrintf(pOut, ")");
      break;
    }
#ifndef SQLITE_OMIT_SUBQUERY
    case TK_EXISTS: {
      sqlite3ExplainPrintf(pOut, "EXISTS(");
      sqlite3ExplainSelect(pOut, pExpr->x.pSelect);
      sqlite3ExplainPrintf(pOut,")");
      break;
    }
    case TK_SELECT: {
      sqlite3ExplainPrintf(pOut, "(");
      sqlite3ExplainSelect(pOut, pExpr->x.pSelect);
      sqlite3ExplainPrintf(pOut, ")");
      break;
    }
    case TK_IN: {
      sqlite3ExplainPrintf(pOut, "IN(");
      sqlite3ExplainExpr(pOut, pExpr->pLeft);
      sqlite3ExplainPrintf(pOut, ",");
      if( ExprHasProperty(pExpr, EP_xIsSelect) ){
        sqlite3ExplainSelect(pOut, pExpr->x.pSelect);
      }else{
        sqlite3ExplainExprList(pOut, pExpr->x.pList);
      }
      sqlite3ExplainPrintf(pOut, ")");
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
      Expr *pX = pExpr->pLeft;
      Expr *pY = pExpr->x.pList->a[0].pExpr;
      Expr *pZ = pExpr->x.pList->a[1].pExpr;
      sqlite3ExplainPrintf(pOut, "BETWEEN(");
      sqlite3ExplainExpr(pOut, pX);
      sqlite3ExplainPrintf(pOut, ",");
      sqlite3ExplainExpr(pOut, pY);
      sqlite3ExplainPrintf(pOut, ",");
      sqlite3ExplainExpr(pOut, pZ);
      sqlite3ExplainPrintf(pOut, ")");
      break;
    }
    case TK_TRIGGER: {
      /* If the opcode is TK_TRIGGER, then the expression is a reference
      ** to a column in the new.* or old.* pseudo-tables available to
      ** trigger programs. In this case Expr.iTable is set to 1 for the
      ** new.* pseudo-table, or 0 for the old.* pseudo-table. Expr.iColumn
      ** is set to the column of the pseudo-table to read, or to -1 to
      ** read the rowid field.
      */
      sqlite3ExplainPrintf(pOut, "%s(%d)", 
          pExpr->iTable ? "NEW" : "OLD", pExpr->iColumn);
      break;
    }
    case TK_CASE: {
      sqlite3ExplainPrintf(pOut, "CASE(");
      sqlite3ExplainExpr(pOut, pExpr->pLeft);
      sqlite3ExplainPrintf(pOut, ",");
      sqlite3ExplainExprList(pOut, pExpr->x.pList);
      break;
    }
#ifndef SQLITE_OMIT_TRIGGER
    case TK_RAISE: {
      const char *zType = "unk";
      switch( pExpr->affinity ){
        case OE_Rollback:   zType = "rollback";  break;
        case OE_Abort:      zType = "abort";     break;
        case OE_Fail:       zType = "fail";      break;
        case OE_Ignore:     zType = "ignore";    break;
      }
      sqlite3ExplainPrintf(pOut, "RAISE-%s(%s)", zType, pExpr->u.zToken);
      break;
    }
#endif
  }
