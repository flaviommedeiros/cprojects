switch( p->op ){
#ifndef SQLITE_OMIT_BLOB_LITERAL
    case TK_BLOB:
#endif
    case TK_VARIABLE:
    case TK_INTEGER:
    case TK_FLOAT:
    case TK_NULL:
    case TK_STRING: {
      testcase( p->op==TK_BLOB );
      testcase( p->op==TK_VARIABLE );
      testcase( p->op==TK_INTEGER );
      testcase( p->op==TK_FLOAT );
      testcase( p->op==TK_NULL );
      testcase( p->op==TK_STRING );
      /* Single-instruction constants with a fixed destination are
      ** better done in-line.  If we factor them, they will just end
      ** up generating an OP_SCopy to move the value to the destination
      ** register. */
      return 0;
    }
    case TK_UMINUS: {
      if( p->pLeft->op==TK_FLOAT || p->pLeft->op==TK_INTEGER ){
        return 0;
      }
      break;
    }
    default: {
      break;
    }
  }
