if ((sv[i].ino == s.st_ino)
#if CHECK_DEVNO_TOO
			 && (sv[i].dev == s.st_dev)
#endif
			) {
				if (sv[i].pid == 0) /* restart if it has died */
					goto run_ith_sv;
				sv[i].isgone = 0; /* "we still see you" */
				goto next_dentry;
			}
