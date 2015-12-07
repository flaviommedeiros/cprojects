#ifdef NUMA_SUPPORT
if (!(fp = fopen(node_boards[numa_index].path_meminfo[i],"r")))
#else
    if (!(fp = fopen(path_meminfo, "r")))
#endif
      {
      rm_errno = RM_ERR_SYSTEM;

      return(NULL);
      }
