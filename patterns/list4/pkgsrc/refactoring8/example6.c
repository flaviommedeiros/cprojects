char *com[] = {
	LCC_LIBPATH "rcc",
#ifdef __ELF__
	"-target=x86/netbsdelf",
#else
	"-target=x86/netbsd",
#endif
	"$1",
	"$2",
	"$3",
	0
};
