#ifdef GTP_RB
if (GTP_RB_PAGE_IS_EMPTY) {
#endif
#if defined(GTP_FRAME_SIMPLE) || defined(GTP_FTRACE_RING_BUFFER)
	if (!gtp_frame) {
#endif
		snprintf(buf, bufmax, "tnotrun:0;");
		buf += 10;
		size += 10;
		bufmax -= 10;
	} else if (!tpe || (tpe && tpe->reason == gtp_stop_normal)) {
		snprintf(buf, bufmax, "tstop:0;");
		buf += 8;
		size += 8;
		bufmax -= 8;
	} else {
		char	outtmp[100];

		switch (tpe->reason) {
		case gtp_stop_frame_full:
			snprintf(buf, bufmax, "tfull:%lx;",
				 (unsigned long)tpe->num);
			break;
		case gtp_stop_efault:
			snprintf(buf, bufmax, "terror:%s:%lx;",
				 string2hex("read memory false", outtmp),
				 (unsigned long)tpe->num);
			break;
		case gtp_stop_access_wrong_reg:
			snprintf(buf, bufmax, "terror:%s:%lx;",
				 string2hex("access wrong register", outtmp),
				 (unsigned long)tpe->num);
			break;
		case gtp_stop_agent_expr_code_error:
			snprintf(buf, bufmax, "terror:%s:%lx;",
				 string2hex("agent expression code error",
					    outtmp),
				 (unsigned long)tpe->num);
			break;
		case gtp_stop_agent_expr_stack_overflow:
			snprintf(buf, bufmax, "terror:%s:%lx;",
				string2hex("agent expression stack overflow",
					   outtmp),
				(unsigned long)tpe->num);
			break;
		default:
			buf[0] = '\0';
			break;
		}

		size += strlen(buf);
		bufmax -= strlen(buf);
		buf += strlen(buf);
	}

	if (atomic_read(&gtp_frame_create)) {
#ifdef GTP_FRAME_SIMPLE
		char	*tmp = gtp_frame_r_start;

		do {
			if (tmp == gtp_frame_end)
				tmp = gtp_frame;

			if (FID(tmp) == FID_HEAD)
				tfnum++;

			tmp = gtp_frame_next(tmp);
			if (!tmp)
				break;
		} while (tmp != gtp_frame_w_start);
#endif
#ifdef GTP_FTRACE_RING_BUFFER
		if (gtp_start) {
			/* XXX: It is just the number of entries.  */
			tfnum = (int)ring_buffer_entries(gtp_frame);
		} else {
			int	old_num = gtp_frame_current_num;
			int	cpu;

			gtp_frame_iter_reset();

			for_each_online_cpu(cpu) {
				char				*tmp;
				struct ring_buffer_event	*rbe;

				while (1) {
					rbe = ring_buffer_read
						(gtp_frame_iter[cpu], NULL);
					if (rbe == NULL)
						break;
					tmp = ring_buffer_event_data(rbe);
					if (FID(tmp) == FID_HEAD)
						tfnum++;
				}
			}

			if (old_num == -1)
				gtp_frame_iter_reset();
			else if (old_num >= 0) {
				gtp_frame_head_find_num(old_num);
				ring_buffer_read
					(gtp_frame_iter[gtp_frame_current_cpu],
					 NULL);
			}
		}
#endif
#ifdef GTP_RB
		int			cpu;
		struct gtp_rb_walk_s	rbws;

		rbws.flags = GTP_RB_WALK_PASS_PAGE | GTP_RB_WALK_CHECK_END;

		for_each_online_cpu(cpu) {
			struct gtp_rb_s	*rb
				= (struct gtp_rb_s *)per_cpu_ptr(gtp_rb, cpu);
			void		*tmp;
			unsigned long	flags;

			GTP_RB_LOCK_IRQ(rb, flags);
			rbws.end = rb->w;
			tmp = rb->r;
			while (1) {
				tmp = gtp_rb_walk(&rbws, tmp);
				if (rbws.reason != gtp_rb_walk_new_entry)
					break;
				tfnum++;
				tmp += FRAME_ALIGN(GTP_FRAME_HEAD_SIZE);
			}
			GTP_RB_UNLOCK_IRQ(rb, flags);
		}
#endif
	}

	snprintf(buf, bufmax, "tframes:%x;", tfnum);
	size += strlen(buf);
	bufmax -= strlen(buf);
	buf += strlen(buf);

	snprintf(buf, bufmax, "tcreated:%x;", atomic_read(&gtp_frame_create));
	size += strlen(buf);
	bufmax -= strlen(buf);
	buf += strlen(buf);

#ifdef GTP_FRAME_SIMPLE
	snprintf(buf, bufmax, "tsize:%x;", GTP_FRAME_SIZE);
#endif
#ifdef GTP_FTRACE_RING_BUFFER
	if (gtp_frame)
		snprintf(buf, bufmax, "tsize:%lx;",
			 ring_buffer_size(gtp_frame));
	else
		snprintf(buf, bufmax, "tsize:%x;",
			 GTP_FRAME_SIZE * num_online_cpus());
#endif
#ifdef GTP_RB
	snprintf(buf, bufmax, "tsize:%lx;",
		 gtp_rb_page_count * GTP_RB_DATA_MAX * num_online_cpus());
#endif
	size += strlen(buf);
	bufmax -= strlen(buf);
	buf += strlen(buf);

#ifdef GTP_FRAME_SIMPLE
	spin_lock(&gtp_frame_lock);
	if (gtp_frame_is_circular)
		tmpaddr = 0;
	else
		tmpaddr = GTP_FRAME_SIZE - (gtp_frame_w_start - gtp_frame);
	spin_unlock(&gtp_frame_lock);
#endif
#ifdef GTP_FTRACE_RING_BUFFER
	/* XXX: Ftrace ring buffer don't have interface to get the size of free
	   buffer. */
	tmpaddr = 0;
#endif
#ifdef GTP_RB
	if (atomic_read(&gtp_frame_create)) {
		int			cpu;

		tmpaddr = 0;
		for_each_online_cpu(cpu) {
			struct gtp_rb_s	*rb
				= (struct gtp_rb_s *)per_cpu_ptr(gtp_rb, cpu);
			void		*tmp;
			unsigned long	flags;

			GTP_RB_LOCK_IRQ(rb, flags);
			tmpaddr += GTP_RB_END(rb->w) - rb->w;
			for (tmp = GTP_RB_NEXT(rb->w);
			     GTP_RB_HEAD(tmp) != GTP_RB_HEAD(rb->r);
			     tmp = GTP_RB_NEXT(tmp))
				tmpaddr += GTP_RB_DATA_MAX;
			tmpaddr += rb->r - GTP_RB_DATA(rb->r);
			GTP_RB_UNLOCK_IRQ(rb, flags);
		}
	} else {
		tmpaddr = gtp_rb_page_count * GTP_RB_DATA_MAX
			  * num_online_cpus();
	}
#endif
	snprintf(buf, bufmax, "tfree:%lx;", (unsigned long)tmpaddr);
	size += strlen(buf);
	bufmax -= strlen(buf);
	buf += strlen(buf);

	snprintf(buf, bufmax, "circular:%x;", gtp_circular);
	size += strlen(buf);
	bufmax -= strlen(buf);
	buf += strlen(buf);

	snprintf(buf, bufmax, "disconn:%x", gtp_disconnected_tracing);
	size += strlen(buf);
	bufmax -= strlen(buf);
	buf += strlen(buf);

	return size;
}
