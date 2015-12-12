#ifdef GTP_FRAME_SIMPLE
if (gtp_start || !gtp_frame_current) {
#elif defined(GTP_FTRACE_RING_BUFFER) || defined(GTP_RB)
	if (gtp_start || gtp_frame_current_num < 0) {
#endif
		if (gtp_current_pid) {
			int ret = gtp_task_read(gtp_current_pid, NULL, addr,
						gtp_m_buffer, (int)len, 0);
			if (ret < 0)
				return ret;
			if (ret != len)
				return -EFAULT;

			goto out;
		} else {
			if (probe_kernel_read(gtp_m_buffer,
					      (void *)(CORE_ADDR)addr,
					      (size_t)len))
				return -EFAULT;
		}
	} else {
#ifdef GTP_FRAME_SIMPLE
		char	*next;
#endif
		int	ret;

		/* XXX: Issue 1: The following part is for gtpro support.
		   It is not available because it make disassemble cannot
		   work when select a trace frame. */
#if 0
		struct gtpro_entry	*gtroe;

		memset(gtp_m_buffer, 0, len);

		/* Read the gtpro.  */
		for (gtroe = gtpro_list; gtroe; gtroe = gtroe->next) {
			CORE_ADDR	cur_start, cur_end;

			cur_start = max(gtroe->start, (CORE_ADDR)addr);
			cur_end = min(gtroe->end, ((CORE_ADDR)(addr + len)));
			if (cur_start < cur_end) {
#ifdef GTP_DEBUG
				printk(GTP_DEBUG "gtp_gdbrsp_m: ro read "
						 "start = 0x%lx end = 0x%lx\n",
				       (unsigned long) cur_start,
				       (unsigned long) cur_end);
#endif
				if (probe_kernel_read(gtp_m_buffer,
						       (void *)cur_start,
						       (size_t)(cur_end
								- cur_start)))
					return -EFAULT;
			}
		}
#endif
		ret = probe_kernel_read(gtp_m_buffer, (void *)(CORE_ADDR)addr,
					(size_t)len);
#ifdef GTP_FRAME_SIMPLE
		for (next = *(char **)(gtp_frame_current + FID_SIZE); next;
		     next = *(char **)(next + FID_SIZE)) {
			if (FID(next) == FID_MEM) {
				struct gtp_frame_mem	*mr;
				ULONGEST		cur_start, cur_end;
				uint8_t			*buf;

				mr = (struct gtp_frame_mem *)
				     (next + FID_SIZE + sizeof(char *));
				buf = next + GTP_FRAME_MEM_SIZE;
#ifdef GTP_DEBUG
				printk(GTP_DEBUG "gtp_gdbrsp_m: section "
						 "addr = 0x%lx size = %lu\n",
				       (unsigned long) mr->addr,
				       (unsigned long) mr->size);
#endif
				cur_start = max(((ULONGEST)mr->addr), addr);
				cur_end = min(((ULONGEST)mr->addr
						+ mr->size),
					       (addr + len));
#ifdef GTP_DEBUG
				printk(GTP_DEBUG "gtp_gdbrsp_m: read "
						 "start = 0x%lx end = 0x%lx\n",
				       (unsigned long) cur_start,
				       (unsigned long) cur_end);
#endif
				if (cur_start < cur_end) {
					memcpy(gtp_m_buffer + cur_start - addr,
						buf + cur_start - mr->addr,
						cur_end - cur_start);
					ret = 0;
				}
			}
		}
#endif
#ifdef GTP_FTRACE_RING_BUFFER
		gtp_frame_head_find_num(gtp_frame_current_num);
		ring_buffer_read(gtp_frame_iter[gtp_frame_current_cpu], NULL);

		while (1) {
			struct ring_buffer_event	*rbe;
			char				*tmp;

			rbe = ring_buffer_iter_peek
				(gtp_frame_iter[gtp_frame_current_cpu], NULL);
			if (rbe == NULL)
				break;
			tmp = ring_buffer_event_data(rbe);
			if (FID(tmp) == FID_HEAD)
				break;
			if (FID(tmp) == FID_MEM) {
				struct gtp_frame_mem	*mr;
				ULONGEST		cur_start, cur_end;
				uint8_t			*buf;

				mr = (struct gtp_frame_mem *)
				     (tmp + FID_SIZE);
				buf = tmp + GTP_FRAME_MEM_SIZE;
#ifdef GTP_DEBUG
				printk(GTP_DEBUG "gtp_gdbrsp_m: section "
						 "addr = 0x%lx size = %lu\n",
				       (unsigned long) mr->addr,
				       (unsigned long) mr->size);
#endif
				cur_start = max(((ULONGEST)mr->addr), addr);
				cur_end = min(((ULONGEST)mr->addr
						+ mr->size),
					       (addr + len));
#ifdef GTP_DEBUG
				printk(GTP_DEBUG "gtp_gdbrsp_m: read "
						 "start = 0x%lx end = 0x%lx\n",
				       (unsigned long) cur_start,
				       (unsigned long) cur_end);
#endif
				if (cur_start < cur_end) {
					memcpy(gtp_m_buffer + cur_start - addr,
						buf + cur_start - mr->addr,
						cur_end - cur_start);
					ret = 0;
				}
			}
			ring_buffer_read(gtp_frame_iter[gtp_frame_current_cpu],
					 NULL);
		}
#endif
#ifdef GTP_RB
		{
			struct gtp_rb_walk_s	rbws;
			char			*tmp;

			rbws.flags = GTP_RB_WALK_PASS_PAGE
				     | GTP_RB_WALK_CHECK_END
				     | GTP_RB_WALK_CHECK_ID
				     | GTP_RB_WALK_CHECK_TYPE;
			rbws.end = gtp_frame_current_rb->w;
			rbws.id = gtp_frame_current_id;
			rbws.type = FID_MEM;
			tmp = gtp_frame_current_rb->rp;

			while (1) {
				struct gtp_frame_mem	*mr;
				ULONGEST		cur_start, cur_end;
				uint8_t			*buf;

				tmp = gtp_rb_walk(&rbws, tmp);
				if (rbws.reason != gtp_rb_walk_type)
					break;

				mr = (struct gtp_frame_mem *) (tmp + FID_SIZE);
				buf = tmp + GTP_FRAME_MEM_SIZE;
#ifdef GTP_DEBUG
				printk(GTP_DEBUG "gtp_gdbrsp_m: section "
						 "addr = 0x%lx size = %lu\n",
				       (unsigned long) mr->addr,
				       (unsigned long) mr->size);
#endif
				cur_start = max(((ULONGEST)mr->addr), addr);
				cur_end = min(((ULONGEST)mr->addr
						+ mr->size),
					       (addr + len));
#ifdef GTP_DEBUG
				printk(GTP_DEBUG "gtp_gdbrsp_m: read "
						 "start = 0x%lx end = 0x%lx\n",
				       (unsigned long) cur_start,
				       (unsigned long) cur_end);
#endif
				if (cur_start < cur_end) {
					memcpy(gtp_m_buffer + cur_start - addr,
						buf + cur_start - mr->addr,
						cur_end - cur_start);
					ret = 0;
				}

				tmp += FRAME_ALIGN(GTP_FRAME_MEM_SIZE
						   + mr->size);
			}
		}
#endif
		if (ret)
			return -EFAULT;
	}

out:
	for (i = 0; i < (int)len; i++) {
#ifdef GTP_DEBUG
		printk(GTP_DEBUG "gtp_gdbrsp_m: %d %02x\n", i, gtp_m_buffer[i]);
#endif
		sprintf(gtp_rw_bufp, "%02x", gtp_m_buffer[i]);
		gtp_rw_bufp += 2;
		gtp_rw_size += 2;
	}

	return 1;
}
