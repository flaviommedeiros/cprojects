#if (SIZEOF_SIZE_T < 8)
if (file_len < ((1ULL)<<32))
#endif
      mem_map = mmap(NULL, file_len,
                     PROT_READ, MAP_SHARED,
                     fileno(read_fp), 0);
