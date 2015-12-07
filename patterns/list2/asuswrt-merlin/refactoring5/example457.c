#ifndef SQLITE_OMIT_EXPLAIN
if( p->explain ){
    rc = sqlite3VdbeList(p);
  }else
#endif /* SQLITE_OMIT_EXPLAIN */
  {
    rc = sqlite3VdbeExec(p);
  }
