if ((central->version_needed != local->version_needed)
#if 0
	/* some zip-files have different values in local
	   and global headers for the bitflags */
	|| (central->bitflags != local->bitflags)
#endif
	|| (central->comp_method != local->comp_method)
	|| (central->last_mod != local->last_mod)
	|| !_zip_string_equal(central->filename, local->filename))
	return -1;
