const int __initconst h8300_saved_vectors[] = {
#if defined(CONFIG_GDB_DEBUG)
	TRACE_VEC,
	TRAP3_VEC,
#endif
	-1
};
