if (!tflag || (get_atdir(
#ifdef NET2_FTS
			    ftent->fts_statb.st_dev, ftent->fts_statb.st_ino,
#else
			    ftent->fts_statp->st_dev, ftent->fts_statp->st_ino,
#endif
			    &mtime, &atime) < 0))
				continue;
