switch (var->type) {
	case gtp_var_special:
		ret = var->u.hooks->agent_set_val(gts, var, val);
		break;
	case gtp_var_per_cpu:
		gtp_var_get_pc(var)->u.val = val;
		break;
	case gtp_var_normal:
		var->u.val = val;
		break;
#ifdef GTP_PERF_EVENTS
	case gtp_var_perf_event_per_cpu:
	case gtp_var_perf_event: {
		struct gtp_var_pe	*pe = gtp_var_get_pe(var);
		pe->pe->val = perf_event_read_value(pe->pe->event,
						    &(pe->pe->enabled),
						    &(pe->pe->running));
		if (pe->ptid == pe_tv_en)
			gtp_pe_set_en(pe->pe, (int)val);
		else {
			/* For pe_tv_val.  */
#if (KGTP_API_VERSION_LOCAL < 20120808)
			gtp_perf_event_set(pe->pe->event, (u64)val);
#else
			perf_event_set(pe->pe->event, (u64)val);
#endif
		}
	}
		break;
#endif
	}
