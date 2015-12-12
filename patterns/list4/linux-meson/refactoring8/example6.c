static struct tracer_opt trace_opts[] = {
#ifdef CONFIG_FUNCTION_GRAPH_TRACER
	/* display latency trace as call graph */
	{ TRACER_OPT(display-graph, TRACE_DISPLAY_GRAPH) },
#endif
	{ } /* Empty entry */
};
