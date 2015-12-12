#ifndef SQLITE_OMIT_VIRTUALTABLE
if( IsVirtual(sWBI.pSrc->pTab) ){
          sWBI.ppIdxInfo = &pWInfo->a[j].pIdxInfo;
          bestVirtualIndex(&sWBI);
        }else 
#endif
        {
          bestBtreeIndex(&sWBI);
        }
