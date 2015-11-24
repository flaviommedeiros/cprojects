#ifdef HWLOC_SOLARIS_SYS
if ((uid_t)0 != geteuid())
    backend->discover = NULL;
  else
#endif
    backend->discover = hwloc_look_pci;
