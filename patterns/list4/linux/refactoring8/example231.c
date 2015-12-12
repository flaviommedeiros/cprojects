static struct sched_domain_topology_level powerpc_topology[] = {
#ifdef CONFIG_SCHED_SMT
	{ cpu_smt_mask, powerpc_smt_flags, SD_INIT_NAME(SMT) },
#endif
	{ cpu_cpu_mask, SD_INIT_NAME(DIE) },
	{ NULL, },
};
