if ((h1->version_needed != h2->version_needed)
#if 0
	/* some zip-files have different values in local
	   and global headers for the bitflags */
	|| (h1->bitflags != h2->bitflags)
#endif
	|| (h1->comp_method != h2->comp_method)
	|| (h1->last_mod != h2->last_mod)
	|| (h1->filename_len != h2->filename_len)
	|| !h1->filename || !h2->filename
	|| strcmp(h1->filename, h2->filename))
	return -1;
