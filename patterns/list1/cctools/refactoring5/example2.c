#ifndef SQLITE_OMIT_WAL
if( iFrame ){
    /* Try to pull the page from the write-ahead log. */
    rc = sqlite3WalReadFrame(pPager->pWal, iFrame, pgsz, pPg->pData);
  }else
#endif
  {
    i64 iOffset = (pgno-1)*(i64)pPager->pageSize;
    rc = sqlite3OsRead(pPager->fd, pPg->pData, pgsz, iOffset);
    if( rc==SQLITE_IOERR_SHORT_READ ){
      rc = SQLITE_OK;
    }
  }
