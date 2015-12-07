if( pNC->ncFlags & NC_IdxExpr )      zIn = "index expressions";
#ifndef SQLITE_OMIT_CHECK
    else if( pNC->ncFlags & NC_IsCheck ) zIn = "CHECK constraints";
#endif
