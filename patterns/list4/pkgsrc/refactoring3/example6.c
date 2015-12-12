switch (mode & S_IFMT) {
	case S_IFDIR:			/* directory */
		*p++ = 'd';
		break;
	case S_IFCHR:			/* character special */
		*p++ = 'c';
		break;
	case S_IFBLK:			/* block special */
		*p++ = 'b';
		break;
	case S_IFREG:			/* regular */
#ifdef S_ARCH2
		if ((mode & S_ARCH2) != 0) {
			*p++ = 'A';
		} else if ((mode & S_ARCH1) != 0) {
			*p++ = 'a';
		} else {
#endif
			*p++ = '-';
#ifdef S_ARCH2
		}
#endif
		break;
	case S_IFLNK:			/* symbolic link */
		*p++ = 'l';
		break;
#ifdef S_IFSOCK
	case S_IFSOCK:			/* socket */
		*p++ = 's';
		break;
#endif
#ifdef S_IFIFO
	case S_IFIFO:			/* fifo */
		*p++ = 'p';
		break;
#endif
#ifdef S_IFWHT
	case S_IFWHT:			/* whiteout */
		*p++ = 'w';
		break;
#endif
#ifdef S_IFDOOR
	case S_IFDOOR:			/* door */
		*p++ = 'D';
		break;
#endif
	default:			/* unknown */
		*p++ = '?';
		break;
	}
