#ifndef SQLITE_OMIT_AUTOMATIC_INDEX
if( (pLevel->plan.wsFlags & WHERE_TEMP_INDEX)!=0 ){
      constructAutomaticIndex(pParse, sWBI.pWC, pTabItem, notReady, pLevel);
    }else
#endif
    if( (pLevel->plan.wsFlags & WHERE_INDEXED)!=0 ){
      Index *pIx = pLevel->plan.u.pIdx;
      KeyInfo *pKey = sqlite3IndexKeyinfo(pParse, pIx);
      int iIndexCur = pLevel->iIdxCur;
      assert( pIx->pSchema==pTab->pSchema );
      assert( iIndexCur>=0 );
      sqlite3VdbeAddOp4(v, OP_OpenRead, iIndexCur, pIx->tnum, iDb,
                        (char*)pKey, P4_KEYINFO_HANDOFF);
      VdbeComment((v, "%s", pIx->zName));
    }
