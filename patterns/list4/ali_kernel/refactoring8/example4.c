static struct tracer_opt func_opts[] = {
#ifdef CONFIG_STACKTRACE
	{ TRACER_OPT(func_stack_trace, TRACE_FUNC_OPT_STACK) },
#endif
	{ } /* Always set a last empty entry */
};
