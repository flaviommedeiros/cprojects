switch (type) {
	case TRACE_REG_REGISTER:
		return enable_trace_probe(tp, TP_FLAG_TRACE);
	case TRACE_REG_UNREGISTER:
		disable_trace_probe(tp, TP_FLAG_TRACE);
		return 0;

#ifdef CONFIG_PERF_EVENTS
	case TRACE_REG_PERF_REGISTER:
		return enable_trace_probe(tp, TP_FLAG_PROFILE);
	case TRACE_REG_PERF_UNREGISTER:
		disable_trace_probe(tp, TP_FLAG_PROFILE);
		return 0;
	case TRACE_REG_PERF_OPEN:
	case TRACE_REG_PERF_CLOSE:
	case TRACE_REG_PERF_ADD:
	case TRACE_REG_PERF_DEL:
		return 0;
#endif
	}
