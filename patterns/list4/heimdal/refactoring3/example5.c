switch (errno) {
#ifdef EFTYPE
	case EFTYPE:
#endif
	case EINVAL:
	    db->hdb_db = dbopen(actual_fn, flags, mode, DB_HASH, NULL);
	}
