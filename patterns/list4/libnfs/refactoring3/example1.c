switch (st.nfs_mode & S_IFMT) {
	#ifndef WIN32
			case S_IFLNK:
				printf("l");
				break;
	#endif
			case S_IFREG:
				printf("-");
				break;
			case S_IFDIR:
				printf("d");
				break;
			case S_IFCHR:
				printf("c");
				break;
			case S_IFBLK:
				printf("b");
				break;
			}
