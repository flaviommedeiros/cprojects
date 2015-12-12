static struct bench_subsys subsystems[] = {
#ifdef LIBNUMA_SUPPORT
	{ "numa",
	  "NUMA scheduling and MM behavior",
	  numa_suites },
#endif
	{ "sched",
	  "scheduler and IPC mechanism",
	  sched_suites },
	{ "mem",
	  "memory access performance",
	  mem_suites },
	{ "all",		/* sentinel: easy for help */
	  "all benchmark subsystem",
	  NULL },
	{ NULL,
	  NULL,
	  NULL       }
};
