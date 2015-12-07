#ifndef SQLITE_OMIT_VIRTUALTABLE
if( IsVirtual(pTab) ){
      const char *pVTab = (const char *)sqlite3GetVTable(db, pTab);
      sqlite3VtabMakeWritable(pParse, pTab);
      sqlite3VdbeAddOp4(v, OP_VUpdate, 1, pTab->nCol+2, regIns, pVTab, P4_VTAB);
      sqlite3VdbeChangeP5(v, onError==OE_Default ? OE_Abort : onError);
      sqlite3MayAbort(pParse);
    }else
#endif
    {
      int isReplace;    /* Set to true if constraints may cause a replace */
      sqlite3GenerateConstraintChecks(pParse, pTab, aRegIdx, iDataCur, iIdxCur,
          regIns, 0, ipkColumn>=0, onError, endOfLoop, &isReplace
      );
      sqlite3FkCheck(pParse, pTab, 0, regIns, 0, 0);
      sqlite3CompleteInsertion(pParse, pTab, iDataCur, iIdxCur,
                               regIns, aRegIdx, 0, appendFlag, isReplace==0);
    }
