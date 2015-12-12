switch (var->type) {
		case gtp_var_special:
			if (var->u.hooks && var->u.hooks->gdb_get_val) {
				ret = var->u.hooks->gdb_get_val(NULL,
								var, &val);
				if (ret)
					return ret;
			} else
				var = NULL;
			break;
#ifdef GTP_PERF_EVENTS
		case gtp_var_perf_event:
		case gtp_var_perf_event_per_cpu: {
			struct gtp_var_pe	*pe = gtp_var_get_pe(var);
			if (pe->ptid == pe_tv_val
			    || pe->ptid == pe_tv_enabled
			    || pe->ptid == pe_tv_running) {
				if (gtp_start)
					pe->pe->val = perf_event_read_value(pe->pe->event,
									    &(pe->pe->enabled),
									    &(pe->pe->running));
			}
			switch (pe->ptid) {
			case pe_tv_val:
				val = (uint64_t)(pe->pe->val);
				break;
			case pe_tv_enabled:
				val = (uint64_t)(pe->pe->enabled);
				break;
			case pe_tv_running:
				val = (uint64_t)(pe->pe->running);
				break;
			default:
				break;
			}
		}
			break;
#endif
		case gtp_var_per_cpu:
			val = gtp_var_get_pc(var)->u.val;
			break;
		default:
			val = var->u.val;
			break;
		}
