switch (var->type) {
	case gtp_var_special:
		ret = var->u.hooks->agent_get_val(gts, var, val);
		break;
	case gtp_var_per_cpu:
		*val = gtp_var_get_pc(var)->u.val;
		break;
	case gtp_var_normal:
		*val = var->u.val;
		break;
#ifdef GTP_PERF_EVENTS
	case gtp_var_perf_event_per_cpu:
	case gtp_var_perf_event: {
			struct gtp_var_pe	*pe = gtp_var_get_pe(var);
			pe->pe->val = perf_event_read_value(pe->pe->event,
							    &(pe->pe->enabled),
							    &(pe->pe->running));
			switch (pe->ptid) {
			case pe_tv_val:
				*val = (int64_t)(pe->pe->val);
				break;
			case pe_tv_enabled:
				*val = (int64_t)(pe->pe->enabled);
				break;
			case pe_tv_running:
				*val = (int64_t)(pe->pe->running);
				break;
			default:
				/* This just to handle warning of gcc.  */
				break;
			}
		}
		break;
#endif
	}
