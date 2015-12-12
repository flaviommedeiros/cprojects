#ifdef _DIRENT_HAVE_D_TYPE
if (d->d_type == DT_DIR || d->d_type == DT_UNKNOWN)
#endif
		{
			struct stat sb;

			if (fstatat(dfd, d->d_name, &sb, AT_SYMLINK_NOFOLLOW)) {
				warn(_("stat of %s failed"), d->d_name);
				continue;
			}

			/* remove subdirectories if device is same as dir */
			if (S_ISDIR(sb.st_mode) && sb.st_dev == rb.st_dev) {
				int cfd;

				cfd = openat(dfd, d->d_name, O_RDONLY);
				if (cfd >= 0) {
					recursiveRemove(cfd);
					close(cfd);
				}
				isdir = 1;
			} else
				continue;
		}
