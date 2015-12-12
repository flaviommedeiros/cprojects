#ifdef HAVE_LUTIMES
if (lutimes(name, times) != 0)
#else
        if ((AE_IFLNK != archive_entry_filetype(entry))
			&& utimes(name, times) != 0)
#endif
                lafe_warnc(errno, "Can't update time for %s", name);
