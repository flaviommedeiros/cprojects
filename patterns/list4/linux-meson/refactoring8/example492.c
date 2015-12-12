const int __initconst h8300_saved_vectors[] = {
#if defined(CONFIG_GDB_DEBUG)
	TRAP3_VEC,	/* TRAPA #3 is GDB breakpoint */
#endif
	-1,
};
