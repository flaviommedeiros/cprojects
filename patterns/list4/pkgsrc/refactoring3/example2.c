switch (type) {
	case F_BLOCK:
		return S_IFBLK;
	case F_CHAR:
		return S_IFCHR;
	case F_DIR:
		return S_IFDIR;
	case F_FIFO:
		return S_IFIFO;
	case F_FILE:
		return S_IFREG;
	case F_LINK:
		return S_IFLNK;
#ifdef S_IFSOCK
	case F_SOCK:
		return S_IFSOCK;
#endif
	default:
		printf("unknown type %d", type);
		abort();
	}
