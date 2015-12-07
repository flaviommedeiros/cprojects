if ((path[1+ src] != LT_PATHSEP_CHAR)
		 && (path[1+ src] != LT_EOS_CHAR)
#if defined(LT_DIRSEP_CHAR)
		 && (path[1+ src] != LT_DIRSEP_CHAR)
#endif
		 && (path[1+ src] != '/'))
	  {
	    canonical[dest++] = '/';
	  }
