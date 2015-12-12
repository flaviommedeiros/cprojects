if (strcmp(path, "./pg_tblspc") == 0 &&
#ifndef WIN32
			S_ISLNK(statbuf.st_mode)
#else
			pgwin32_is_junction(pathbuf)
#endif
			)
		{
#if defined(HAVE_READLINK) || defined(WIN32)
			char		linkpath[MAXPGPATH];
			int			rllen;

			rllen = readlink(pathbuf, linkpath, sizeof(linkpath));
			if (rllen < 0)
				ereport(ERROR,
						(errcode_for_file_access(),
						 errmsg("could not read symbolic link \"%s\": %m",
								pathbuf)));
			if (rllen >= sizeof(linkpath))
				ereport(ERROR,
						(errmsg("symbolic link \"%s\" target is too long",
								pathbuf)));
			linkpath[rllen] = '\0';

			if (!sizeonly)
				_tarWriteHeader(pathbuf + basepathlen + 1, linkpath, &statbuf);
			size += 512;		/* Size of the header just added */
#else

			/*
			 * If the platform does not have symbolic links, it should not be
			 * possible to have tablespaces - clearly somebody else created
			 * them. Warn about it and ignore.
			 */
			ereport(WARNING,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				  errmsg("tablespaces are not supported on this platform")));
			continue;
#endif   /* HAVE_READLINK */
		}
		else if (S_ISDIR(statbuf.st_mode))
		{
			bool		skip_this_dir = false;
			ListCell   *lc;

			/*
			 * Store a directory entry in the tar file so we can get the
			 * permissions right.
			 */
			if (!sizeonly)
				_tarWriteHeader(pathbuf + basepathlen + 1, NULL, &statbuf);
			size += 512;		/* Size of the header just added */

			/*
			 * Call ourselves recursively for a directory, unless it happens
			 * to be a separate tablespace located within PGDATA.
			 */
			foreach(lc, tablespaces)
			{
				tablespaceinfo *ti = (tablespaceinfo *) lfirst(lc);

				/*
				 * ti->rpath is the tablespace relative path within PGDATA, or
				 * NULL if the tablespace has been properly located somewhere
				 * else.
				 *
				 * Skip past the leading "./" in pathbuf when comparing.
				 */
				if (ti->rpath && strcmp(ti->rpath, pathbuf + 2) == 0)
				{
					skip_this_dir = true;
					break;
				}
			}
			if (!skip_this_dir)
				size += sendDir(pathbuf, basepathlen, sizeonly, tablespaces);
		}
		else if (S_ISREG(statbuf.st_mode))
		{
			bool		sent = false;

			if (!sizeonly)
				sent = sendFile(pathbuf, pathbuf + basepathlen + 1, &statbuf,
								true);

			if (sent || sizeonly)
			{
				/* Add size, rounded up to 512byte block */
				size += ((statbuf.st_size + 511) & ~511);
				size += 512;	/* Size of the header of the file */
			}
		}
		else
			ereport(WARNING,
					(errmsg("skipping special file \"%s\"", pathbuf)));
