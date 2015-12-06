#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
if( eCall==STAT_GET_STAT1 )
#else
  assert( argc==1 );
