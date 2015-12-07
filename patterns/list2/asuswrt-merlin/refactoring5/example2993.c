#ifndef SQLITE_OMIT_VIRTUALTABLE
if( IsVirtual(pTabItem->pTab) ){
          sqlite3_index_info **pp = &pWInfo->a[j].pIdxInfo;
          bestVirtualIndex(pParse, pWC, pTabItem, mask, pOrderBy, &sCost, pp);
        }else 
#endif
        {
          bestBtreeIndex(pParse, pWC, pTabItem, mask, pOrderBy, &sCost);
        }
