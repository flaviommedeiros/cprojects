#ifdef GTP_PERF_EVENTS
if (cvar->type != gtp_var_per_cpu
			    && cvar->type != gtp_var_perf_event_per_cpu)
#else
			if (cvar->type != gtp_var_per_cpu)
#endif
				continue;
