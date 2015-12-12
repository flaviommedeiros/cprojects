#ifdef GTP_FRAME_SIMPLE
if (gtp_start || !gtp_frame_current) {
#elif defined(GTP_FTRACE_RING_BUFFER) || defined(GTP_RB)
	if (gtp_start || gtp_frame_current_num < 0) {
#endif
		var = gtp_var_find_num(num);
		if (var == NULL)
			goto out;

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
	} else {
#ifdef GTP_FRAME_SIMPLE
		char	*next;

		for (next = *(char **)(gtp_frame_current + FID_SIZE); next;
		     next = *(char **)(next + FID_SIZE)) {
			if (FID(next) == FID_VAR) {
				vr = (struct gtp_frame_var *)
				     (next + FID_SIZE + sizeof(char *));
				if (vr->num == (unsigned int)num)
					goto while_stop;
			}
		}
#endif
#ifdef GTP_FTRACE_RING_BUFFER
		int				is_first = 1;
		struct ring_buffer_event	*rbe;
		char				*tmp;

		/* Handle $cpu_id and $clock.  */
		if (num == GTP_VAR_CLOCK_ID) {
			val = gtp_frame_current_clock;
			goto output_value;
		}
		else if (num == GTP_VAR_CPU_ID) {
			val = gtp_frame_current_cpu;
			goto output_value;
		}
re_find:
		while (1) {
			rbe = ring_buffer_iter_peek
				(gtp_frame_iter[gtp_frame_current_cpu], NULL);
			if (rbe == NULL)
				break;
			tmp = ring_buffer_event_data(rbe);
			if (FID(tmp) == FID_HEAD)
				break;
			if (FID(tmp) == FID_VAR) {
				vr = (struct gtp_frame_var *)(tmp + FID_SIZE);
				if (vr->num == (unsigned int)num)
					goto while_stop;
			}
			ring_buffer_read(gtp_frame_iter[gtp_frame_current_cpu],
					 NULL);
		}
		if (is_first) {
			gtp_frame_head_find_num(gtp_frame_current_num);
			ring_buffer_read(gtp_frame_iter[gtp_frame_current_cpu],
					 NULL);
			is_first = 0;
			goto re_find;
		}
#endif
#if defined(GTP_FRAME_SIMPLE) || defined(GTP_FTRACE_RING_BUFFER)
		vr = NULL;
while_stop:
		if (vr)
			val = vr->val;
	}
#endif
#ifdef GTP_RB
		if (gtp_rb_traceframe_get_tv(gtp_frame_current_rb->rp,
					     gtp_frame_current_id,
					     (unsigned int)num, &val) == 0)
			goto output_value;
	}
