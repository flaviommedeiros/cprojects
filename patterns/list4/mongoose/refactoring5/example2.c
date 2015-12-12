#ifndef SQLITE_OMIT_INCRBLOB
if( pCur->aOverflow && pCur->aOverflow[iIdx+1] ){
          nextPage = pCur->aOverflow[iIdx+1];
        } else 
#endif
          rc = getOverflowPage(pBt, nextPage, 0, &nextPage);
