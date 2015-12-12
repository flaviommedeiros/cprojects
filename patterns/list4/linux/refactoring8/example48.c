const struct option options[] = {
		OPT_INCR('v', "verbose", &verbose, "be more verbose"),
		OPT_STRING('i', "input", &input_name, "file", "input file name"),
#ifdef HAVE_LIBBABELTRACE_SUPPORT
		OPT_STRING(0, "to-ctf", &to_ctf, NULL, "Convert to CTF format"),
#endif
		OPT_BOOLEAN('f', "force", &force, "don't complain, do it"),
		OPT_END()
	};
