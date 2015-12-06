#if (SIZEOF_SIZE_T < 8)
if (file_len < ((1LL)<<32))
#endif
			mem_map = mmap(NULL, file_len,
			               PROT_READ, MAP_SHARED,
			               fileno(word_file), 0);
