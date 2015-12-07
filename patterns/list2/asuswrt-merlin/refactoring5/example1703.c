#ifdef HAVE_COMPRESSION
if (DB_IS_COMPRESSED(dbc->dbp)) {
		if (countp != NULL)
			*countp = comp_count;
	} else
#endif
	if (countp != NULL)
		*countp = count;
