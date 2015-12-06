#ifndef SQLITE_OMIT_EXPLAIN
if( p->explain ){
    rc = sqlite3VdbeList(p);
  }else
#endif /* SQLITE_OMIT_EXPLAIN */
  {
    db->vdbeExecCnt++;
    rc = sqlite3VdbeExec(p);
    db->vdbeExecCnt--;
  }
