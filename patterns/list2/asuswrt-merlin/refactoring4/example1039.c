#ifdef O_NOFOLLOW
if((ofd = sys_open (dest, O_WRONLY | O_CREAT | O_TRUNC | O_NOFOLLOW, 0600)) < 0 )
#else
	if((ofd = sys_open (dest, O_WRONLY | O_CREAT | O_TRUNC , 0600)) < 0 )
#endif
		goto err;
