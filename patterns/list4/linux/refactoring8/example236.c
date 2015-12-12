static const char *nvram_os_partitions[] = {
#ifdef CONFIG_PPC_PSERIES
	"ibm,rtas-log",
#endif
	"lnx,oops-log",
	NULL
};
