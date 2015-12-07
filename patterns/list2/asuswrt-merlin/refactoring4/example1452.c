#ifdef LINUX26
if (!action || ((!interface || !product) && !is_block))
#else
	if (!interface || !action || !product)	/* Hubs bail out here. */
#endif
		return;
