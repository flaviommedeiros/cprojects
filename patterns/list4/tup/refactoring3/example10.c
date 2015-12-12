switch( opcode ){
      case OP_Transaction: {
        if( pOp->p2!=0 ) p->readOnly = 0;
        /* fall thru */
      }
      case OP_AutoCommit:
      case OP_Savepoint: {
        p->bIsReader = 1;
        break;
      }
#ifndef SQLITE_OMIT_WAL
      case OP_Checkpoint:
#endif
      case OP_Vacuum:
      case OP_JournalMode: {
        p->readOnly = 0;
        p->bIsReader = 1;
        break;
      }
#ifndef SQLITE_OMIT_VIRTUALTABLE
      case OP_VUpdate: {
        if( pOp->p2>nMaxArgs ) nMaxArgs = pOp->p2;
        break;
      }
      case OP_VFilter: {
        int n;
        assert( p->nOp - i >= 3 );
        assert( pOp[-1].opcode==OP_Integer );
        n = pOp[-1].p1;
        if( n>nMaxArgs ) nMaxArgs = n;
        break;
      }
#endif
      case OP_Next:
      case OP_NextIfOpen:
      case OP_SorterNext: {
        pOp->p4.xAdvance = sqlite3BtreeNext;
        pOp->p4type = P4_ADVANCE;
        break;
      }
      case OP_Prev:
      case OP_PrevIfOpen: {
        pOp->p4.xAdvance = sqlite3BtreePrevious;
        pOp->p4type = P4_ADVANCE;
        break;
      }
    }
