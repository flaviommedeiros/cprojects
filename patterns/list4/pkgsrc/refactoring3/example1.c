switch(s->type) {
	case F_BLOCK:
		if (!S_ISBLK(p->fts_statp->st_mode))
			goto typeerr;
		break;
	case F_CHAR:
		if (!S_ISCHR(p->fts_statp->st_mode))
			goto typeerr;
		break;
	case F_DIR:
		if (!S_ISDIR(p->fts_statp->st_mode))
			goto typeerr;
		break;
	case F_FIFO:
		if (!S_ISFIFO(p->fts_statp->st_mode))
			goto typeerr;
		break;
	case F_FILE:
		if (!S_ISREG(p->fts_statp->st_mode))
			goto typeerr;
		break;
	case F_LINK:
		if (!S_ISLNK(p->fts_statp->st_mode))
			goto typeerr;
		break;
#ifdef S_ISSOCK
	case F_SOCK:
		if (!S_ISSOCK(p->fts_statp->st_mode))
			goto typeerr;
		break;
#endif
typeerr:		LABEL;
		printf("\ttype (%s, %s)\n",
		    nodetype(s->type), inotype(p->fts_statp->st_mode));
		return (label);
	}
