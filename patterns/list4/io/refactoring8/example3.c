int
callsystem_open(const char * filename,
				enum callsystem_filemode mode,
				callsystem_fd_t fd[2])
{
#ifdef unix
	switch(mode & ~CALLSYSTEM_MODE_BINARY)
	{
		case CALLSYSTEM_MODE_READ:
			fd[1] = CALLSYSTEM_ILG_FD;
			fd[0] = open(filename, O_RDONLY);
			if(fd[0] == -1)
				return -1;
			break;
			case CALLSYSTEM_MODE_CREATE:
			fd[0] = CALLSYSTEM_ILG_FD;
			fd[1] = open(filename, O_WRONLY|O_CREAT|O_EXCL, 0774);
			if(fd[1] == -1)
				return -1;
			break;
			case CALLSYSTEM_MODE_APPEND:
			fd[0] = CALLSYSTEM_ILG_FD;
			fd[1] = open(filename, O_WRONLY|O_APPEND);
			if(fd[1] == -1)
				return -1;
			break;
			case CALLSYSTEM_MODE_OVERWRITE:
			fd[0] = CALLSYSTEM_ILG_FD;
			fd[1] = open(filename, O_WRONLY|O_CREAT|O_TRUNC, 0774);
			if(fd[1] == -1)
				return -1;
			break;
			default:
			errno = EINVAL;
			return -1;
	}
#elif defined(WIN32)
	/*TODO*/
	(void) filename;
	(void) mode;
	(void) fd;
#endif
	return 0;
}
