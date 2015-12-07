if ((path[src] != '/')
#if defined(LT_DIRSEP_CHAR)
	    && (path[src] != LT_DIRSEP_CHAR)
#endif
	    )
	  {
	    canonical[dest++] = path[src];
	  }
	/* Directory separators are converted and copied only if they are
	   not at the end of a path -- i.e. before a path separator or
	   NULL terminator.  */
	else if ((path[1+ src] != LT_PATHSEP_CHAR)
		 && (path[1+ src] != LT_EOS_CHAR)
#if defined(LT_DIRSEP_CHAR)
		 && (path[1+ src] != LT_DIRSEP_CHAR)
#endif
		 && (path[1+ src] != '/'))
	  {
	    canonical[dest++] = '/';
	  }
