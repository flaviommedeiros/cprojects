#ifdef CONFIG_SLIP_MODE_SLIP6
if (sl->mode & SL_MODE_SLIP6)
			slip_unesc6(sl, *cp++);
		else
#endif
			slip_unesc(sl, *cp++);
