switch (var->type) {
	case gtp_var_special:
		if (arg == GTP_VAR_SELF_TRACE_ID) {
			tpe->flags |= GTP_ENTRY_FLAGS_SELF_TRACE;
			ret = 1;
			goto out;
		} else if (arg == GTP_VAR_BT_ID) {
			ret = gtp_add_backtrace_actions (tpe, step);
			goto out;
		} else if (arg == GTP_VAR_CURRENT_ID) {
			tpe->flags |= GTP_ENTRY_FLAGS_CURRENT_TASK;
			ret = 1;
			goto out;
		}

		if (arg == GTP_VAR_COOKED_CLOCK_ID)
			gtp_access_cooked_clock = 1;
#ifdef CONFIG_X86
		else if (arg == GTP_VAR_COOKED_RDTSC_ID)
			gtp_access_cooked_rdtsc = 1;
#endif
		if (!var->u.hooks || (var->u.hooks
				      && !var->u.hooks->agent_get_val)) {
			printk(KERN_WARNING "Action try to get special TSV %d that cannot be get.\n",
				arg);
			ret = -EINVAL;
			goto out;
		}
		break;

#ifdef GTP_PERF_EVENTS
	case gtp_var_perf_event_per_cpu:
	case gtp_var_perf_event: {
			struct gtp_var_pe	*pe = gtp_var_get_pe(var);

			if (pe->ptid != pe_tv_val
			    && pe->ptid != pe_tv_enabled
			    && pe->ptid != pe_tv_running) {
				printk(KERN_WARNING "Action try to get perf event TSV %d that cannot be get.\n",
				arg);
				goto out;
			}
			if (var->type == gtp_var_perf_event
			    && gtp_x_var_add(list, arg, 1)) {
				ret = -ENOMEM;
				goto out;
			}
		}
		break;
#endif

	case gtp_var_normal:
		if (gtp_x_var_add(list, arg, 1)) {
			ret = -ENOMEM;
			goto out;
		}
		break;
	}
