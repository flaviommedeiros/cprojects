const char * const probe_usage[] = {
		"perf probe [<options>] 'PROBEDEF' ['PROBEDEF' ...]",
		"perf probe [<options>] --add 'PROBEDEF' [--add 'PROBEDEF' ...]",
		"perf probe [<options>] --del '[GROUP:]EVENT' ...",
		"perf probe --list",
#ifdef DWARF_SUPPORT
		"perf probe [<options>] --line 'LINEDESC'",
		"perf probe [<options>] --vars 'PROBEPOINT'",
#endif
		NULL
};
