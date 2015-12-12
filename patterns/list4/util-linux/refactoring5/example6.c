#ifdef HAVE_LIBREADLINE
if (isatty(STDIN_FILENO)) {
			if (!rl_fgets(buf, bufsz, stdout, prompt)) {
				if (fdisk_label_is_changed(fdisk_get_label(cxt, NULL))) {
					if (rl_fgets(buf, bufsz, stderr,
							_("\nDo you really want to quit? "))
							&& !rpmatch(buf))
						continue;
				}
				fdisk_unref_context(cxt);
				exit(EXIT_FAILURE);
			} else
				break;
		}
		else
#endif
		{
			fputs(prompt, stdout);
			fflush(stdout);
			if (!fgets(buf, bufsz, stdin)) {
				if (fdisk_label_is_changed(fdisk_get_label(cxt, NULL))) {
					fprintf(stderr, _("\nDo you really want to quit? "));

					if (fgets(buf, bufsz, stdin) && !rpmatch(buf))
						continue;
				}
				fdisk_unref_context(cxt);
				exit(EXIT_FAILURE);
			} else
				break;
		}
