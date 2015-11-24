switch (e) {
	case EACCES:
	case EPERM:
	case EROFS:
		return CHIRP_ERROR_NOT_AUTHORIZED;
	case ENOENT:
		return CHIRP_ERROR_DOESNT_EXIST;
	case EEXIST:
		return CHIRP_ERROR_ALREADY_EXISTS;
	case EFBIG:
		return CHIRP_ERROR_TOO_BIG;
	case ENOSPC:
	case EDQUOT:
		return CHIRP_ERROR_NO_SPACE;
	case ENOMEM:
		return CHIRP_ERROR_NO_MEMORY;
#ifdef ENOATTR
	case ENOATTR:
#endif
	case ENOSYS:
	case EINVAL:
		return CHIRP_ERROR_INVALID_REQUEST;
	case EMFILE:
	case ENFILE:
		return CHIRP_ERROR_TOO_MANY_OPEN;
	case EBUSY:
		return CHIRP_ERROR_BUSY;
	case EAGAIN:
		return CHIRP_ERROR_TRY_AGAIN;
	case EBADF:
		return CHIRP_ERROR_BAD_FD;
	case EISDIR:
		return CHIRP_ERROR_IS_DIR;
	case ENOTDIR:
		return CHIRP_ERROR_NOT_DIR;
	case ENOTEMPTY:
		return CHIRP_ERROR_NOT_EMPTY;
	case EXDEV:
		return CHIRP_ERROR_CROSS_DEVICE_LINK;
	case EHOSTUNREACH:
		return CHIRP_ERROR_GRP_UNREACHABLE;
	case ESRCH:
		return CHIRP_ERROR_NO_SUCH_JOB;
	case ESPIPE:
		return CHIRP_ERROR_IS_A_PIPE;
	case ENAMETOOLONG:
		return CHIRP_ERROR_NAME_TOO_LONG;
	case ENOTSUP:
		return CHIRP_ERROR_NOT_SUPPORTED;
	default:
		debug(D_CHIRP, "zoiks, I don't know how to transform error %d (%s)\n", errno, strerror(errno));
		return CHIRP_ERROR_UNKNOWN;
	}
