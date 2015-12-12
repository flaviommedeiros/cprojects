static PSI_file_info all_mysys_files[]=
{
#ifdef HUGETLB_USE_PROC_MEMINFO
  { &key_file_proc_meminfo, "proc_meminfo", 0},
#endif /* HUGETLB_USE_PROC_MEMINFO */
  { &key_file_charset, "charset", 0},
  { &key_file_cnf, "cnf", 0}
};
