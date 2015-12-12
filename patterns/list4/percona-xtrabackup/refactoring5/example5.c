#ifdef EXDEV
if (r != ARCHIVE_OK && archive_errno(cpio->archive) == EXDEV) {
			/* Cross-device link:  Just fall through and use
			 * the original entry to copy the file over. */
			lafe_warnc(0, "Copying file instead");
		} else
#endif
		return (0);
