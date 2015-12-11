switch (ERRNO) {
#ifdef EACCES
  case EACCES:
    fprintf(errors,"You don't have permission to create %s.\n", name);
    break;
#endif
#ifdef ENAMETOOLONG
  case ENAMETOOLONG:
    fprintf(errors,"The directory name %s is too long.\n", name);
    break;
#endif
#ifdef EROFS
  case EROFS:
    fprintf(errors,"%s resides on a read-only file system.\n", name);
    break;
#endif
#ifdef ENOSPC
  case ENOSPC:
    fprintf(errors,"No space left on the file system that will "
            "contain the directory %s.\n", name);
    break;
#endif
#ifdef EDQUOT
  case EDQUOT:
    fprintf(errors,"Cannot create directory %s because you "
            "exceeded your quota.\n", name);
    break;
#endif
  default :
    fprintf(errors,"Error creating directory %s.\n", name);
    break;
  }
