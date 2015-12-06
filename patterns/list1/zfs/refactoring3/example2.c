switch (what & S_IFMT) {
	case S_IFBLK:
		symbol = 'B';
		break;
	case S_IFCHR:
		symbol = 'C';
		break;
	case S_IFDIR:
		symbol = '/';
		break;
#ifdef S_IFDOOR
	case S_IFDOOR:
		symbol = '>';
		break;
#endif
	case S_IFIFO:
		symbol = '|';
		break;
	case S_IFLNK:
		symbol = '@';
		break;
#ifdef S_IFPORT
	case S_IFPORT:
		symbol = 'P';
		break;
#endif
	case S_IFSOCK:
		symbol = '=';
		break;
	case S_IFREG:
		symbol = 'F';
		break;
	default:
		symbol = '?';
		break;
	}
