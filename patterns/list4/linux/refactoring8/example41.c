static struct collection collections[] = {
	{ "sched",	"Scheduler and IPC benchmarks",			sched_benchmarks	},
	{ "mem",	"Memory access benchmarks",			mem_benchmarks		},
#ifdef HAVE_LIBNUMA_SUPPORT
	{ "numa",	"NUMA scheduling and MM benchmarks",		numa_benchmarks		},
#endif
	{"futex",       "Futex stressing benchmarks",                   futex_benchmarks        },
	{ "all",	"All benchmarks",				NULL			},
	{ NULL,		NULL,						NULL			}
};
