switch( pExpr->op ){
    case TK_AGG_COLUMN: {
      sqlite3TreeViewLine(pView, "AGG{%d:%d}",
            pExpr->iTable, pExpr->iColumn);
      break;
    }
    case TK_COLUMN: {
      if( pExpr->iTable<0 ){
        /* This only happens when coding check constraints */
        sqlite3TreeViewLine(pView, "COLUMN(%d)", pExpr->iColumn);
      }else{
        sqlite3TreeViewLine(pView, "{%d:%d}",
                             pExpr->iTable, pExpr->iColumn);
      }
      break;
    }
    case TK_INTEGER: {
      if( pExpr->flags & EP_IntValue ){
        sqlite3TreeViewLine(pView, "%d", pExpr->u.iValue);
      }else{
        sqlite3TreeViewLine(pView, "%s", pExpr->u.zToken);
      }
      break;
    }
#ifndef SQLITE_OMIT_FLOATING_POINT
    case TK_FLOAT: {
      sqlite3TreeViewLine(pView,"%s", pExpr->u.zToken);
      break;
    }
#endif
    case TK_STRING: {
      sqlite3TreeViewLine(pView,"%Q", pExpr->u.zToken);
      break;
    }
    case TK_NULL: {
      sqlite3TreeViewLine(pView,"NULL");
      break;
    }
#ifndef SQLITE_OMIT_BLOB_LITERAL
    case TK_BLOB: {
      sqlite3TreeViewLine(pView,"%s", pExpr->u.zToken);
      break;
    }
#endif
    case TK_VARIABLE: {
      sqlite3TreeViewLine(pView,"VARIABLE(%s,%d)",
                          pExpr->u.zToken, pExpr->iColumn);
      break;
    }
    case TK_REGISTER: {
      sqlite3TreeViewLine(pView,"REGISTER(%d)", pExpr->iTable);
      break;
    }
    case TK_AS: {
      sqlite3TreeViewLine(pView,"AS %Q", pExpr->u.zToken);
      sqlite3TreeViewExpr(pView, pExpr->pLeft, 0);
      break;
    }
    case TK_ID: {
      sqlite3TreeViewLine(pView,"ID %Q", pExpr->u.zToken);
      break;
    }
#ifndef SQLITE_OMIT_CAST
    case TK_CAST: {
      /* Expressions of the form:   CAST(pLeft AS token) */
      sqlite3TreeViewLine(pView,"CAST %Q", pExpr->u.zToken);
      sqlite3TreeViewExpr(pView, pExpr->pLeft, 0);
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
    case TK_DOT:     zBinOp = "DOT";    break;

    case TK_UMINUS:  zUniOp = "UMINUS"; break;
    case TK_UPLUS:   zUniOp = "UPLUS";  break;
    case TK_BITNOT:  zUniOp = "BITNOT"; break;
    case TK_NOT:     zUniOp = "NOT";    break;
    case TK_ISNULL:  zUniOp = "ISNULL"; break;
    case TK_NOTNULL: zUniOp = "NOTNULL"; break;

    case TK_COLLATE: {
      sqlite3TreeViewLine(pView, "COLLATE %Q", pExpr->u.zToken);
      sqlite3TreeViewExpr(pView, pExpr->pLeft, 0);
      break;
    }

    case TK_AGG_FUNCTION:
    case TK_FUNCTION: {
      ExprList *pFarg;       /* List of function arguments */
      if( ExprHasProperty(pExpr, EP_TokenOnly) ){
        pFarg = 0;
      }else{
        pFarg = pExpr->x.pList;
      }
      if( pExpr->op==TK_AGG_FUNCTION ){
        sqlite3TreeViewLine(pView, "AGG_FUNCTION%d %Q",
                             pExpr->op2, pExpr->u.zToken);
      }else{
        sqlite3TreeViewLine(pView, "FUNCTION %Q", pExpr->u.zToken);
      }
      if( pFarg ){
        sqlite3TreeViewExprList(pView, pFarg, 0, 0);
      }
      break;
    }
#ifndef SQLITE_OMIT_SUBQUERY
    case TK_EXISTS: {
      sqlite3TreeViewLine(pView, "EXISTS-expr");
      sqlite3TreeViewSelect(pView, pExpr->x.pSelect, 0);
      break;
    }
    case TK_SELECT: {
      sqlite3TreeViewLine(pView, "SELECT-expr");
      sqlite3TreeViewSelect(pView, pExpr->x.pSelect, 0);
      break;
    }
    case TK_IN: {
      sqlite3TreeViewLine(pView, "IN");
      sqlite3TreeViewExpr(pView, pExpr->pLeft, 1);
      if( ExprHasProperty(pExpr, EP_xIsSelect) ){
        sqlite3TreeViewSelect(pView, pExpr->x.pSelect, 0);
      }else{
        sqlite3TreeViewExprList(pView, pExpr->x.pList, 0, 0);
      }
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
      sqlite3TreeViewLine(pView, "BETWEEN");
      sqlite3TreeViewExpr(pView, pX, 1);
      sqlite3TreeViewExpr(pView, pY, 1);
      sqlite3TreeViewExpr(pView, pZ, 0);
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
      sqlite3TreeViewLine(pView, "%s(%d)", 
          pExpr->iTable ? "NEW" : "OLD", pExpr->iColumn);
      break;
    }
    case TK_CASE: {
      sqlite3TreeViewLine(pView, "CASE");
      sqlite3TreeViewExpr(pView, pExpr->pLeft, 1);
      sqlite3TreeViewExprList(pView, pExpr->x.pList, 0, 0);
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
      sqlite3TreeViewLine(pView, "RAISE %s(%Q)", zType, pExpr->u.zToken);
      break;
    }
#endif
    default: {
      sqlite3TreeViewLine(pView, "op=%d", pExpr->op);
      break;
    }
  }
