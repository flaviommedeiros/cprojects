MTAB cpu_mod[] = {
	{ UNIT_MSIZE,      4096, NULL,   "4KW",  &cpu_set_size},
	{ UNIT_MSIZE,      8192, NULL,   "8KW",  &cpu_set_size},
	{ UNIT_MSIZE,     16384, NULL,   "16KW", &cpu_set_size},
	{ UNIT_MSIZE,     32768, NULL,   "32KW", &cpu_set_size},
#ifdef ENABLE_1800_SUPPORT
	{ UNIT_1800,          0, "1130", "1130", &cpu_set_type},
	{ UNIT_1800,  UNIT_1800, "1800", "1800", &cpu_set_type},
#endif	
	{ UNIT_TRACE, UNIT_TRACE_NONE,  "notrace",    "NOTRACE",    NULL},
	{ UNIT_TRACE, UNIT_TRACE_IO,    "traceIO",    "TRACEIO",    NULL},
	{ UNIT_TRACE, UNIT_TRACE_INSTR, "traceInstr", "TRACEINSTR", NULL},
	{ UNIT_TRACE, UNIT_TRACE_BOTH,  "traceBoth",  "TRACEBOTH",  NULL},
	{ 0 }  };
