if (!archive_entry_atime_is_set(a->entry)
#if HAVE_STRUCT_STAT_ST_BIRTHTIME
	    && !archive_entry_birthtime_is_set(a->entry)
#endif
	    && !archive_entry_mtime_is_set(a->entry))
		return (ARCHIVE_OK);
