switch (cmd) {
	case F_GETFD:
	case F_GETFL:
	case F_GETOWN:
	case F_GETSIG:
	case F_GETLEASE:
		LOG("%s 0x%x void\n", __func__, real_fd);
		return _std_fcntl(real_fd, cmd);

	case F_DUPFD:
#ifdef F_DUPFD_CLOEXEC
	case F_DUPFD_CLOEXEC:
#endif // F_DUPFD_CLOEXEC
	case F_SETFD:
	case F_SETFL:
	case F_SETOWN:
	case F_SETSIG:
	case F_SETLEASE:
	case F_NOTIFY:
	{
		long arg;
		va_start(args, cmd);
		arg = va_arg(args, long);
		va_end(args);
		LOG("%s 0x%x long 0x%lx\n", __func__, real_fd, arg);
		return _std_fcntl(real_fd, cmd, arg);
	}

	case F_SETLK:
	case F_SETLKW:
	case F_GETLK:
	{
		struct flock *flk;
		va_start(args, cmd);
		flk = va_arg(args, struct flock *);
		va_end(args);
		LOG("%s 0x%x lock %p\n", __func__, real_fd, flk);
		return _std_fcntl(real_fd, cmd, flk);
	}

#if __WORDSIZE == 32
	case F_SETLK64:
	case F_SETLKW64:
	case F_GETLK64:
	{
		struct flock64 *flk;
		va_start(args, cmd);
		flk = va_arg(args, struct flock64 *);
		va_end(args);
		LOG("%s 0x%x lock64 %p (%p)\n",
		    __func__, real_fd, flk, _std_fcntl);
		return _std_fcntl(real_fd, cmd, flk);
	}
#endif

	default:
		LOG("%s unrecognized cmd\n", __func__);
		errno = EINVAL;
		return -1;
	}
