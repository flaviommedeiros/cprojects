switch (type) {
	case TRACE_REG_REGISTER:
		return probe_event_enable(tu, TP_FLAG_TRACE, NULL);

	case TRACE_REG_UNREGISTER:
		probe_event_disable(tu, TP_FLAG_TRACE);
		return 0;

#ifdef CONFIG_PERF_EVENTS
	case TRACE_REG_PERF_REGISTER:
		return probe_event_enable(tu, TP_FLAG_PROFILE, uprobe_perf_filter);

	case TRACE_REG_PERF_UNREGISTER:
		probe_event_disable(tu, TP_FLAG_PROFILE);
		return 0;

	case TRACE_REG_PERF_OPEN:
		return uprobe_perf_open(tu, data);

	case TRACE_REG_PERF_CLOSE:
		return uprobe_perf_close(tu, data);

#endif
	default:
		return 0;
	}