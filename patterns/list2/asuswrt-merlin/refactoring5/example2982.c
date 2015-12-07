#ifndef SQLITE_OMIT_VIRTUALTABLE
if( IsVirtual(pTab) ){
      const char *pVTab = (const char *)sqlite3GetVTable(db, pTab);
      sqlite3VtabMakeWritable(pParse, pTab);
      sqlite3VdbeAddOp4(v, OP_VUpdate, 1, pTab->nCol+2, regIns, pVTab, P4_VTAB);
      sqlite3MayAbort(pParse);
    }else
#endif
    {
      int isReplace;    /* Set to true if constraints may cause a replace */
      sqlite3GenerateConstraintChecks(pParse, pTab, baseCur, regIns, aRegIdx,
          keyColumn>=0, 0, onError, endOfLoop, &isReplace
      );
      sqlite3FkCheck(pParse, pTab, 0, regIns);
      sqlite3CompleteInsertion(
          pParse, pTab, baseCur, regIns, aRegIdx, 0, appendFlag, isReplace==0
      );
    }
