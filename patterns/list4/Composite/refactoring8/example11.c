int __libc_start_main(int (*main)(int,char **,char **), int argc, char **argv)
{
	char **envp = argv+argc+1;

#ifndef SHARED
	__init_libc(envp, argv[0]);
	_init();
	uintptr_t a = (uintptr_t)&__init_array_start;
	for (; a<(uintptr_t)&__init_array_end; a+=sizeof(void(*)()))
		(*(void (**)())a)();
#endif

	/* Pass control to the application */
	exit(main(argc, argv, envp));
	return 0;
}
