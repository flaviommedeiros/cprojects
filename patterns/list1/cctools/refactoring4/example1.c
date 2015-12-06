#if !HAVE_LOCALTIME_R && !HAVE_LOCALTIME_S
if( sqlite3GlobalConfig.bLocaltimeFault ) pX = 0;
