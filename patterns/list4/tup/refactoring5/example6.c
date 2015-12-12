#ifndef SQLITE_OMIT_VIRTUALTABLE
if( IsVirtual(pTab) ){
      const char *pVTab = (const char *)sqlite3GetVTable(db, pTab);
      sqlite3VtabMakeWritable(pParse, pTab);
      sqlite3VdbeAddOp4(v, OP_VUpdate, 0, 1, iKey, pVTab, P4_VTAB);
      sqlite3VdbeChangeP5(v, OE_Abort);
      assert( eOnePass==ONEPASS_OFF || eOnePass==ONEPASS_SINGLE );
      sqlite3MayAbort(pParse);
      if( eOnePass==ONEPASS_SINGLE && sqlite3IsToplevel(pParse) ){
        pParse->isMultiWrite = 0;
      }
    }else
#endif
    {
      int count = (pParse->nested==0);    /* True to count changes */
      int iIdxNoSeek = -1;
      if( bComplex==0 && aiCurOnePass[1]!=iDataCur ){
        iIdxNoSeek = aiCurOnePass[1];
      }
      sqlite3GenerateRowDelete(pParse, pTab, pTrigger, iDataCur, iIdxCur,
          iKey, nKey, count, OE_Default, eOnePass, iIdxNoSeek);
    }
