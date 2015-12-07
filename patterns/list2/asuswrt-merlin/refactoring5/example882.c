#ifdef CONFIG_SLIP_MODE_SLIP6
if(sl->mode & SL_MODE_SLIP6)
		count = slip_esc6(p, (unsigned char *) sl->xbuff, len);
	else
#endif
		count = slip_esc(p, (unsigned char *) sl->xbuff, len);
