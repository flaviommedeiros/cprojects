#ifndef SQLITE_OMIT_VIRTUALTABLE
if( IsVirtual(p->pSrc->pTab) ){
    sqlite3_index_info *pIdxInfo = 0;
    p->ppIdxInfo = &pIdxInfo;
    bestVirtualIndex(p);
    assert( pIdxInfo!=0 || p->pParse->db->mallocFailed );
    if( pIdxInfo && pIdxInfo->needToFreeIdxStr ){
      sqlite3_free(pIdxInfo->idxStr);
    }
    sqlite3DbFree(p->pParse->db, pIdxInfo);
  }else
#endif
  {
    bestBtreeIndex(p);
  }
