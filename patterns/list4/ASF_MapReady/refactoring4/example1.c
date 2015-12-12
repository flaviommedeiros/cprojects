#ifdef __MWERKS__
if ((fd->dalfd = open(fd->fname,opflg)) == -1)
#else
        if ((fd->dalfd = open(fd->fname,opflg,0777)) == -1)
#endif
          {
	   perror("doopen-dal");
           c_errmsg("Error opening file","doopen-open",NON_FATAL);
           return(E_FAIL);
          }
