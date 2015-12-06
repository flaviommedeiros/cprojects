switch (sb->st_mode & S_IFMT) {
	case S_IFDIR:
		if (file_printf (ms, "directory") == -1)
			return -1;
		return 1;
#ifdef S_IFCHR
	case S_IFCHR:
		/* 
		 * If -s has been specified, treat character special files
		 * like ordinary files.  Otherwise, just report that they
		 * are block special files and go on to the next file.
		 */
		if ((ms->flags & R_MAGIC_DEVICES) != 0)
			break;
#ifdef HAVE_STAT_ST_RDEV
# ifdef dv_unit
		if (file_printf (ms, "character special (%d/%d/%d)",
		    major (sb->st_rdev), dv_unit(sb->st_rdev),
		    dv_subunit (sb->st_rdev)) == -1)
			return -1;
# else
		if (file_printf (ms, "character special (%ld/%ld)",
		    (long) major (sb->st_rdev), (long) minor(sb->st_rdev)) == -1)
			return -1;
# endif
#else
		if (file_printf (ms, "character special") == -1)
			return -1;
#endif
		return 1;
#endif
#ifdef S_IFBLK
	case S_IFBLK:
		/* 
		 * If -s has been specified, treat block special files
		 * like ordinary files.  Otherwise, just report that they
		 * are block special files and go on to the next file.
		 */
		if ((ms->flags & R_MAGIC_DEVICES) != 0)
			break;
#ifdef HAVE_STAT_ST_RDEV
# ifdef dv_unit
		if (file_printf(ms, "block special (%d/%d/%d)",
		    major(sb->st_rdev), dv_unit(sb->st_rdev),
		    dv_subunit(sb->st_rdev)) == -1)
			return -1;
# else
		if (file_printf(ms, "block special (%ld/%ld)",
		    (long)major(sb->st_rdev), (long)minor(sb->st_rdev)) == -1)
			return -1;
# endif
#else
		if (file_printf(ms, "block special") == -1)
			return -1;
#endif
		return 1;
#endif
	/* TODO add code to handle V7 MUX and Blit MUX files */
#ifdef	S_IFIFO
	case S_IFIFO:
		if((ms->flags & R_MAGIC_DEVICES) != 0)
			break;
		if (file_printf(ms, "fifo (named pipe)") == -1)
			return -1;
		return 1;
#endif
#ifdef	S_IFDOOR
	case S_IFDOOR:
		return (file_printf (ms, "door") == -1)? -1:1;
#endif
#ifdef	S_IFLNK
	case S_IFLNK:
		if ((nch = readlink (fn, buf, BUFSIZ-1)) <= 0) {
			if (ms->flags & R_MAGIC_ERROR) {
			    file_error (ms, errno, "unreadable symlink `%s'", fn);
			    return -1;
			}
			if (file_printf(ms,
			    "unreadable symlink `%s' (%s)", fn,
			    strerror(errno)) == -1)
				return -1;
			return 1;
		}
		buf[nch] = '\0';	/* readlink(2) does not do this */

		/* If broken symlink, say so and quit early. */
		if (*buf == '/') {
			if (stat(buf, &tstatbuf) < 0)
				return bad_link(ms, errno, buf);
		} else {
			char *tmp;
			char buf2[BUFSIZ+BUFSIZ+4];

			if ((tmp = strrchr(fn,  '/')) == NULL) {
				tmp = buf; /* in current directory anyway */
			} else {
				if (tmp - fn + 1 > BUFSIZ) {
					if (ms->flags & R_MAGIC_ERROR) {
						file_error (ms, 0, "path too long: `%s'", buf);
						return -1;
					}
					if (file_printf (ms, "path too long: `%s'", fn) == -1)
						return -1;
					return 1;
				}
				snprintf (buf2, sizeof (buf2), "%s%s", fn, buf);
				tmp = buf2;
			}
			if (stat (tmp, &tstatbuf) < 0)
				return bad_link(ms, errno, buf);
		}

		/* Otherwise, handle it. */
		if ((ms->flags & R_MAGIC_SYMLINK) != 0) {
			const char *p;
			ms->flags &= R_MAGIC_SYMLINK;
			p = r_magic_file(ms, buf);
			ms->flags |= R_MAGIC_SYMLINK;
			return p != NULL ? 1 : -1;
		} else { /* just print what it points to */
			if (file_printf (ms, "symbolic link to `%s'", buf) == -1)
				return -1;
		}
	return 1;
#endif
#ifdef	S_IFSOCK
	case S_IFSOCK:
		if (file_printf(ms, "socket") == -1)
			return -1;
		return 1;
#endif
	case S_IFREG:
		break;
	default:
		file_error (ms, 0, "invalid mode 0%o", sb->st_mode);
		return -1;
		/*NOTREACHED*/
	}
