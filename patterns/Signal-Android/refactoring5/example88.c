#ifdef UP_fsetmod
if (b->flags&BIO_FLAGS_UPLINK)
			UP_fsetmod(b->ptr,(char)((num&BIO_FP_TEXT)?'t':'b'));
		else
#endif
		{
#if defined(OPENSSL_SYS_WINDOWS)
		int fd = _fileno((FILE*)ptr);
		if (num & BIO_FP_TEXT)
			_setmode(fd,_O_TEXT);
		else
			_setmode(fd,_O_BINARY);
#elif defined(OPENSSL_SYS_NETWARE) && defined(NETWARE_CLIB)
		int fd = fileno((FILE*)ptr);
		/* Under CLib there are differences in file modes */
		if (num & BIO_FP_TEXT)
			setmode(fd,O_TEXT);
		else
			setmode(fd,O_BINARY);
#elif defined(OPENSSL_SYS_MSDOS)
		int fd = fileno((FILE*)ptr);
		/* Set correct text/binary mode */
		if (num & BIO_FP_TEXT)
			_setmode(fd,_O_TEXT);
		/* Dangerous to set stdin/stdout to raw (unless redirected) */
		else
			{
			if (fd == STDIN_FILENO || fd == STDOUT_FILENO)
				{
				if (isatty(fd) <= 0)
					_setmode(fd,_O_BINARY);
				}
			else
				_setmode(fd,_O_BINARY);
			}
#elif defined(OPENSSL_SYS_OS2) || defined(OPENSSL_SYS_WIN32_CYGWIN)
		int fd = fileno((FILE*)ptr);
		if (num & BIO_FP_TEXT)
			setmode(fd, O_TEXT);
		else
			setmode(fd, O_BINARY);
#endif
		}
