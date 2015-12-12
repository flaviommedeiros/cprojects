if (((st->st_mode & S_IFMT) == S_IFREG &&
			      archive_entry_filetype(entry) == AE_IFREG)
#ifdef S_IFLNK
			  ||((st->st_mode & S_IFMT) == S_IFLNK &&
			      archive_entry_filetype(entry) == AE_IFLNK)
#endif
#ifdef S_IFSOCK
			  ||((st->st_mode & S_IFSOCK) == S_IFSOCK &&
			      archive_entry_filetype(entry) == AE_IFSOCK)
#endif
#ifdef S_IFCHR
			  ||((st->st_mode & S_IFMT) == S_IFCHR &&
			      archive_entry_filetype(entry) == AE_IFCHR)
#endif
#ifdef S_IFBLK
			  ||((st->st_mode & S_IFMT) == S_IFBLK &&
			      archive_entry_filetype(entry) == AE_IFBLK)
#endif
			  ||((st->st_mode & S_IFMT) == S_IFDIR &&
			      archive_entry_filetype(entry) == AE_IFDIR)
#ifdef S_IFIFO
			  ||((st->st_mode & S_IFMT) == S_IFIFO &&
			      archive_entry_filetype(entry) == AE_IFIFO)
#endif
			) {
				/* Types match. */
			} else {
				/* Types don't match; bail out gracefully. */
				if (mtree->fd >= 0)
					close(mtree->fd);
				mtree->fd = -1;
				if (parsed_kws & MTREE_HAS_OPTIONAL) {
					/* It's not an error for an optional
					 * entry to not match disk. */
					*use_next = 1;
				} else if (r == ARCHIVE_OK) {
					archive_set_error(&a->archive,
					    ARCHIVE_ERRNO_MISC,
					    "mtree specification has different"
					    " type for %s",
					    archive_entry_pathname(entry));
					r = ARCHIVE_WARN;
				}
				return (r);
			}
