if( opcode==OP_Destroy || opcode==OP_VUpdate || opcode==OP_VRename 
#ifndef SQLITE_OMIT_FOREIGN_KEY
     || (opcode==OP_FkCounter && pOp->p1==0 && pOp->p2==1) 
#endif
     || ((opcode==OP_Halt || opcode==OP_HaltIfNull) 
      && ((pOp->p1&0xff)==SQLITE_CONSTRAINT && pOp->p2==OE_Abort))
    ){
      hasAbort = 1;
      break;
    }
