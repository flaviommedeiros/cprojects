switch (method)
	{
			/*
			 * enum values for all sync options are defined even if they are
			 * not supported on the current platform.  But if not, they are
			 * not included in the enum option array, and therefore will never
			 * be seen here.
			 */
		case SYNC_METHOD_FSYNC:
		case SYNC_METHOD_FSYNC_WRITETHROUGH:
		case SYNC_METHOD_FDATASYNC:
			return 0;
#ifdef OPEN_SYNC_FLAG
		case SYNC_METHOD_OPEN:
			return OPEN_SYNC_FLAG | o_direct_flag;
#endif
#ifdef OPEN_DATASYNC_FLAG
		case SYNC_METHOD_OPEN_DSYNC:
			return OPEN_DATASYNC_FLAG | o_direct_flag;
#endif
		default:
			/* can't happen (unless we are out of sync with option array) */
			elog(ERROR, "unrecognized wal_sync_method: %d", method);
			return 0;			/* silence warning */
	}
