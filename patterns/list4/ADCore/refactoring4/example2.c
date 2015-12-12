#ifdef __crayx1
if(ffflush(nciop->fd,&stat) < 0)
#else
	if(ffflush(nciop->fd) < 0)
#endif
		return errno;
