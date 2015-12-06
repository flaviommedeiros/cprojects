#if defined (__NOT_NEEDED_ANY_MORE___) && defined (__CYGWIN__)
if (select(tty_fd + 1, &set, NULL, NULL, &tv) <= 0)
		//if (!(select(tty_fd + 1, &set, NULL, NULL, &tv) && FD_ISSET(tty_fd, &set)))
			return -1;
