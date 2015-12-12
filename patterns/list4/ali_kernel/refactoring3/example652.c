switch (var->type) {
	case gtp_var_special:
		switch (arg) {
		case GTP_VAR_SELF_TRACE_ID:
			tpe->flags |= GTP_ENTRY_FLAGS_SELF_TRACE;
			ret = 1;
			goto out;
			break;
		case GTP_VAR_KRET_ID:
			/* XXX: still not set it value to maxactive.  */
			tpe->flags |= GTP_ENTRY_FLAGS_IS_KRETPROBE;
			ret = 1;
			goto out;
			break;
		case GTP_VAR_BT_ID:
			ret = gtp_add_backtrace_actions (tpe, step);
			goto out;
			break;
		case GTP_VAR_CURRENT_ID:
			tpe->flags |= GTP_ENTRY_FLAGS_CURRENT_TASK;
			ret = 2;
			break;
		case GTP_VAR_PRINTK_LEVEL_ID:
			if (loop || step) {
				printk(KERN_WARNING "Loop or step action doesn't support printk.\n");
				goto out;
			} else
				tpe->flags |= GTP_ENTRY_FLAGS_HAVE_PRINTK;
			break;
#ifdef CONFIG_X86
		case GTP_WATCH_STATIC_ID:
			if (stack == NULL || top > 1) {
				printk(KERN_WARNING "$watch_static just support set to 0 or 1.\n");
				goto out;
			}
			/* Init watch struct inside gtp_entry.  */
			if (tpe->type != gtp_entry_watch_static
			    && tpe->type != gtp_entry_watch_dynamic) {
				tpe->type = gtp_entry_watch_dynamic;
				tpe->u.watch.type = gtp_watch_write;
				tpe->u.watch.size = 1;
			}
			gtp_have_watch_tracepoint = 1;
			if (top == 1)
				tpe->type = gtp_entry_watch_static;
			else
				tpe->type = gtp_entry_watch_dynamic;
			ret = 1;
			goto out;
			break;
		case GTP_WATCH_TYPE_ID:
			if (stack && (tpe->type == gtp_entry_watch_static
				      || tpe->type == gtp_entry_watch_dynamic)) {
				if (top != gtp_watch_exec
				    && top != gtp_watch_write
				    && top != gtp_watch_read_write) {
					printk(KERN_WARNING "$watch_type just support set to 0, 1 or 2.\n");
					goto out;
				}
				tpe->u.watch.type = top;
				ret = 1;
				goto out;
			}
			break;
		case GTP_WATCH_SIZE_ID:
			if (stack && (tpe->type == gtp_entry_watch_static
				      || tpe->type == gtp_entry_watch_dynamic)) {
				if (top != 1 && top != 2 && top != 4
				    && top != 8) {
					printk(KERN_WARNING "$watch_size just support set to 1, 2, 4 or 8.\n");
					goto out;
				}
				tpe->u.watch.size = top;
				ret = 1;
				goto out;
			}
			break;
#endif
		}

		if (!var->u.hooks || (var->u.hooks
				      && !var->u.hooks->agent_set_val)) {
			printk(KERN_WARNING "Action try to set special TSV %d that cannot be get.\n",
			       arg);
			goto out;
		}
		break;

#ifdef GTP_PERF_EVENTS
	case gtp_var_perf_event_per_cpu:
	case gtp_var_perf_event: {
			struct gtp_var_pe	*pe = gtp_var_get_pe(var);

			if (pe->ptid != pe_tv_en
			    && pe->ptid != pe_tv_val) {
				printk(KERN_WARNING "Action try to set perf event TSV %d that cannot be set.\n",
				arg);
				goto out;
			}
			if (var->type == gtp_var_perf_event
			    && gtp_x_var_add(list, arg, 2)) {
				ret = -ENOMEM;
				goto out;
			}
		}
		break;
#endif

	case gtp_var_normal:
		if (gtp_x_var_add(list, arg, 2)) {
			ret = -ENOMEM;
			goto out;
		}
		break;
	}
