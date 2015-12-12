switch (type) {
	case TRACE_REG_REGISTER:
		return enable_trace_probe(tp, file);
	case TRACE_REG_UNREGISTER:
		return disable_trace_probe(tp, file);

#ifdef CONFIG_PERF_EVENTS
	case TRACE_REG_PERF_REGISTER:
		return enable_trace_probe(tp, NULL);
	case TRACE_REG_PERF_UNREGISTER:
		return disable_trace_probe(tp, NULL);
	case TRACE_REG_PERF_OPEN:
	case TRACE_REG_PERF_CLOSE:
	case TRACE_REG_PERF_ADD:
	case TRACE_REG_PERF_DEL:
		return 0;
#endif
	}
