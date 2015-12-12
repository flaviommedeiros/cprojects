FILE *
callsystem_fdopen(callsystem_fd_t fds[2], enum callsystem_filemode mode)
{
#ifdef unix
	switch(mode & ~CALLSYSTEM_MODE_BINARY)
	{
		case CALLSYSTEM_MODE_READ:
			return fdopen(fds[0], "r");
		case CALLSYSTEM_MODE_WRITE:
			return fdopen(fds[1], "w");
		case CALLSYSTEM_MODE_CREATE:
			return fdopen(fds[1], "w+");
		case CALLSYSTEM_MODE_APPEND:
			return fdopen(fds[1], "a");
		case CALLSYSTEM_MODE_OVERWRITE:
			return fdopen(fds[1], "w+");
		default:
			errno = EINVAL;
			return NULL;
	}
#elif defined(WIN32)

	int which;
	int osf_mode = 0;
	int fd;

	if(mode & CALLSYSTEM_MODE_BINARY)
		osf_mode = 0;
	else
		osf_mode = _O_TEXT;

	if((mode & ~CALLSYSTEM_MODE_BINARY) == CALLSYSTEM_MODE_READ)
		fd = _open_osfhandle(fds[0], osf_mode | _O_RDONLY);
	else
		fd = _open_osfhandle(fds[0], osf_mode | _O_APPEND);
	if(fd == -1)
		return NULL;

	if(mode & CALLSYSTEM_MODE_BINARY)
		switch(mode & ~CALLSYSTEM_MODE_BINARY)
	{
		case CALLSYSTEM_MODE_READ:
			return fdopen(fd, "rb");
		case CALLSYSTEM_MODE_WRITE:
			return fdopen(fd, "wb");
		case CALLSYSTEM_MODE_CREATE:
			return fdopen(fd, "wb+");
		case CALLSYSTEM_MODE_APPEND:
			return fdopen(fd, "ab");
		case CALLSYSTEM_MODE_OVERWRITE:
			return fdopen(fd, "wb+");
		default:
			errno = EINVAL;
			return NULL;
	}
	else
		switch(mode & ~CALLSYSTEM_MODE_BINARY)
	{
		case CALLSYSTEM_MODE_READ:
			return fdopen(fd, "r");
		case CALLSYSTEM_MODE_WRITE:
			return fdopen(fd, "w");
		case CALLSYSTEM_MODE_CREATE:
			return fdopen(fd, "w+");
		case CALLSYSTEM_MODE_APPEND:
			return fdopen(fd, "a");
		case CALLSYSTEM_MODE_OVERWRITE:
			return fdopen(fd, "w+");
		default:
			errno = EINVAL;
			return NULL;
	}

#elif 0
	switch(mode)
	{
			/*| CALLSYSTEM_MODE_BINARY */
		case CALLSYSTEM_MODE_READ:
			return fdopen(fds[0], "r");
		case CALLSYSTEM_MODE_WRITE:
			return fdopen(fds[1], "w");
		case CALLSYSTEM_MODE_CREATE:
			return fdopen(fds[1], "w+");
		case CALLSYSTEM_MODE_APPEND:
			return fdopen(fds[1], "a");
		case CALLSYSTEM_MODE_OVERWRITE:
			return fdopen(fds[1], "w+");
		default:
			errno = EINVAL;
			return NULL;
	}
#endif
}
