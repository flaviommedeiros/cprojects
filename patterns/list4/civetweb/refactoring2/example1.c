#if SQLITE_ENABLE_API_ARMOR
if( p->id==SQLITE_MUTEX_FAST || p->id==SQLITE_MUTEX_RECURSIVE )
#endif
  {
    pthread_mutex_destroy(&p->mutex);
    sqlite3_free(p);
  }
#ifdef SQLITE_ENABLE_API_ARMOR
  else{
    (void)SQLITE_MISUSE_BKPT;
  }
