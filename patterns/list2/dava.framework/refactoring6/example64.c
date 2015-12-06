if ((fd = open(randomfiles[i], O_RDONLY
#ifdef O_NONBLOCK
			|O_NONBLOCK
#endif
#ifdef O_BINARY
			|O_BINARY
#endif
#ifdef O_NOCTTY /* If it happens to be a TTY (god forbid), do not make it
		   our controlling tty */
			|O_NOCTTY
#endif
			)) >= 0)
			{
			int usec = 10*1000; /* spend 10ms on each file */
			int r;
			unsigned int j;
			struct stat *st=&randomstats[i];

			/* Avoid using same input... Used to be O_NOFOLLOW
			 * above, but it's not universally appropriate... */
			if (fstat(fd,st) != 0)	{ close(fd); continue; }
			for (j=0;j<i;j++)
				{
				if (randomstats[j].st_ino==st->st_ino &&
				    randomstats[j].st_dev==st->st_dev)
					break;
				}
			if (j<i)		{ close(fd); continue; }

			do
				{
				int try_read = 0;

#if defined(OPENSSL_SYS_BEOS_R5)
				/* select() is broken in BeOS R5, so we simply
				 *  try to read something and snooze if we couldn't */
				try_read = 1;

#elif defined(OPENSSL_SYS_LINUX)
				/* use poll() */
				struct pollfd pset;
				
				pset.fd = fd;
				pset.events = POLLIN;
				pset.revents = 0;

				if (poll(&pset, 1, usec / 1000) < 0)
					usec = 0;
				else
					try_read = (pset.revents & POLLIN) != 0;

#else
				/* use select() */
				fd_set fset;
				struct timeval t;
				
				t.tv_sec = 0;
				t.tv_usec = usec;

				if (FD_SETSIZE > 0 && (unsigned)fd >= FD_SETSIZE)
					{
					/* can't use select, so just try to read once anyway */
					try_read = 1;
					}
				else
					{
					FD_ZERO(&fset);
					FD_SET(fd, &fset);
					
					if (select(fd+1,&fset,NULL,NULL,&t) >= 0)
						{
						usec = t.tv_usec;
						if (FD_ISSET(fd, &fset))
							try_read = 1;
						}
					else
						usec = 0;
					}
#endif
				
				if (try_read)
					{
					r = read(fd,(unsigned char *)tmpbuf+n, ENTROPY_NEEDED-n);
					if (r > 0)
						n += r;
#if defined(OPENSSL_SYS_BEOS_R5)
					if (r == 0)
						snooze(t.tv_usec);
#endif
					}
				else
					r = -1;
				
				/* Some Unixen will update t in select(), some
				   won't.  For those who won't, or if we
				   didn't use select() in the first place,
				   give up here, otherwise, we will do
				   this once again for the remaining
				   time. */
				if (usec == 10*1000)
					usec = 0;
				}
			while ((r > 0 ||
			       (errno == EINTR || errno == EAGAIN)) && usec != 0 && n < ENTROPY_NEEDED);

			close(fd);
			}
