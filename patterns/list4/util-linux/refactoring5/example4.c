#ifdef HAVE_INOTIFY_INIT
if (follow_by_inotify(in, filename, out) == 0)
		return NULL;				/* file already closed */
	else
#endif
		/* fallback for systems without inotify or with non-free
		 * inotify instances */
		for (;;) {
			while (fread(&ut, sizeof(ut), 1, in) == 1)
				print_utline(&ut, out);
			sleep(1);
		}
