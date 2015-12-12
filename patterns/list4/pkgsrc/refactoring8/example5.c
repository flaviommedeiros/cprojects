char *cpp[] = {
	LCC_LIBPATH "cpp",
	"-D__STDC__=1",
#ifdef __ELF__
	"-D__ELF__",
#else
	"",
#endif
	"-Di386",
	"-D__NetBSD__",
	"-D__KPRINTF_ATTRIBUTE__",
	"-D__STRICT_ANSI__",
	"", /* _POSIX_SOURCE */
	"$1",
	"$2",
	"$3",
	0
};
