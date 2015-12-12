switch (cmd) {

	/* --- capabilities ------------------------------------------ */
	case VIDIOC_QUERYCAP:
	{
		struct v4l2_capability *cap = (struct v4l2_capability *)arg;

		if (!ops->vidioc_querycap)
			break;

		ret = ops->vidioc_querycap(file, fh, cap);
		if (!ret)
			dbgarg(cmd, "driver=%s, card=%s, bus=%s, "
					"version=0x%08x, "
					"capabilities=0x%08x\n",
					cap->driver, cap->card, cap->bus_info,
					cap->version,
					cap->capabilities);
		break;
	}

	/* --- priority ------------------------------------------ */
	case VIDIOC_G_PRIORITY:
	{
		enum v4l2_priority *p = arg;

		if (!ops->vidioc_g_priority)
			break;
		ret = ops->vidioc_g_priority(file, fh, p);
		if (!ret)
			dbgarg(cmd, "priority is %d\n", *p);
		break;
	}
	case VIDIOC_S_PRIORITY:
	{
		enum v4l2_priority *p = arg;

		if (!ops->vidioc_s_priority)
			break;
		dbgarg(cmd, "setting priority to %d\n", *p);
		ret = ops->vidioc_s_priority(file, fh, *p);
		break;
	}

	/* --- capture ioctls ---------------------------------------- */
	case VIDIOC_ENUM_FMT:
	{
		struct v4l2_fmtdesc *f = arg;

		switch (f->type) {
		case V4L2_BUF_TYPE_VIDEO_CAPTURE:
			if (ops->vidioc_enum_fmt_vid_cap)
				ret = ops->vidioc_enum_fmt_vid_cap(file, fh, f);
			break;
		case V4L2_BUF_TYPE_VIDEO_OVERLAY:
			if (ops->vidioc_enum_fmt_vid_overlay)
				ret = ops->vidioc_enum_fmt_vid_overlay(file,
					fh, f);
			break;
		case V4L2_BUF_TYPE_VIDEO_OUTPUT:
			if (ops->vidioc_enum_fmt_vid_out)
				ret = ops->vidioc_enum_fmt_vid_out(file, fh, f);
			break;
		case V4L2_BUF_TYPE_PRIVATE:
			if (ops->vidioc_enum_fmt_type_private)
				ret = ops->vidioc_enum_fmt_type_private(file,
								fh, f);
			break;
		default:
			break;
		}
		if (!ret)
			dbgarg(cmd, "index=%d, type=%d, flags=%d, "
				"pixelformat=%c%c%c%c, description='%s'\n",
				f->index, f->type, f->flags,
				(f->pixelformat & 0xff),
				(f->pixelformat >>  8) & 0xff,
				(f->pixelformat >> 16) & 0xff,
				(f->pixelformat >> 24) & 0xff,
				f->description);
		break;
	}
	case VIDIOC_G_FMT:
	{
		struct v4l2_format *f = (struct v4l2_format *)arg;

		/* FIXME: Should be one dump per type */
		dbgarg(cmd, "type=%s\n", prt_names(f->type, v4l2_type_names));

		switch (f->type) {
		case V4L2_BUF_TYPE_VIDEO_CAPTURE:
			if (ops->vidioc_g_fmt_vid_cap)
				ret = ops->vidioc_g_fmt_vid_cap(file, fh, f);
			if (!ret)
				v4l_print_pix_fmt(vfd, &f->fmt.pix);
			break;
		case V4L2_BUF_TYPE_VIDEO_OVERLAY:
			if (ops->vidioc_g_fmt_vid_overlay)
				ret = ops->vidioc_g_fmt_vid_overlay(file,
								    fh, f);
			break;
		case V4L2_BUF_TYPE_VIDEO_OUTPUT:
			if (ops->vidioc_g_fmt_vid_out)
				ret = ops->vidioc_g_fmt_vid_out(file, fh, f);
			if (!ret)
				v4l_print_pix_fmt(vfd, &f->fmt.pix);
			break;
		case V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY:
			if (ops->vidioc_g_fmt_vid_out_overlay)
				ret = ops->vidioc_g_fmt_vid_out_overlay(file,
				       fh, f);
			break;
		case V4L2_BUF_TYPE_VBI_CAPTURE:
			if (ops->vidioc_g_fmt_vbi_cap)
				ret = ops->vidioc_g_fmt_vbi_cap(file, fh, f);
			break;
		case V4L2_BUF_TYPE_VBI_OUTPUT:
			if (ops->vidioc_g_fmt_vbi_out)
				ret = ops->vidioc_g_fmt_vbi_out(file, fh, f);
			break;
		case V4L2_BUF_TYPE_SLICED_VBI_CAPTURE:
			if (ops->vidioc_g_fmt_sliced_vbi_cap)
				ret = ops->vidioc_g_fmt_sliced_vbi_cap(file,
									fh, f);
			break;
		case V4L2_BUF_TYPE_SLICED_VBI_OUTPUT:
			if (ops->vidioc_g_fmt_sliced_vbi_out)
				ret = ops->vidioc_g_fmt_sliced_vbi_out(file,
									fh, f);
			break;
		case V4L2_BUF_TYPE_PRIVATE:
			if (ops->vidioc_g_fmt_type_private)
				ret = ops->vidioc_g_fmt_type_private(file,
								fh, f);
			break;
		}

		break;
	}
	case VIDIOC_S_FMT:
	{
		struct v4l2_format *f = (struct v4l2_format *)arg;

		/* FIXME: Should be one dump per type */
		dbgarg(cmd, "type=%s\n", prt_names(f->type, v4l2_type_names));

		switch (f->type) {
		case V4L2_BUF_TYPE_VIDEO_CAPTURE:
			CLEAR_AFTER_FIELD(f, fmt.pix);
			v4l_print_pix_fmt(vfd, &f->fmt.pix);
			if (ops->vidioc_s_fmt_vid_cap)
				ret = ops->vidioc_s_fmt_vid_cap(file, fh, f);
			break;
		case V4L2_BUF_TYPE_VIDEO_OVERLAY:
			CLEAR_AFTER_FIELD(f, fmt.win);
			if (ops->vidioc_s_fmt_vid_overlay)
				ret = ops->vidioc_s_fmt_vid_overlay(file,
								    fh, f);
			break;
		case V4L2_BUF_TYPE_VIDEO_OUTPUT:
			CLEAR_AFTER_FIELD(f, fmt.pix);
			v4l_print_pix_fmt(vfd, &f->fmt.pix);
			if (ops->vidioc_s_fmt_vid_out)
				ret = ops->vidioc_s_fmt_vid_out(file, fh, f);
			break;
		case V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY:
			CLEAR_AFTER_FIELD(f, fmt.win);
			if (ops->vidioc_s_fmt_vid_out_overlay)
				ret = ops->vidioc_s_fmt_vid_out_overlay(file,
					fh, f);
			break;
		case V4L2_BUF_TYPE_VBI_CAPTURE:
			CLEAR_AFTER_FIELD(f, fmt.vbi);
			if (ops->vidioc_s_fmt_vbi_cap)
				ret = ops->vidioc_s_fmt_vbi_cap(file, fh, f);
			break;
		case V4L2_BUF_TYPE_VBI_OUTPUT:
			CLEAR_AFTER_FIELD(f, fmt.vbi);
			if (ops->vidioc_s_fmt_vbi_out)
				ret = ops->vidioc_s_fmt_vbi_out(file, fh, f);
			break;
		case V4L2_BUF_TYPE_SLICED_VBI_CAPTURE:
			CLEAR_AFTER_FIELD(f, fmt.sliced);
			if (ops->vidioc_s_fmt_sliced_vbi_cap)
				ret = ops->vidioc_s_fmt_sliced_vbi_cap(file,
									fh, f);
			break;
		case V4L2_BUF_TYPE_SLICED_VBI_OUTPUT:
			CLEAR_AFTER_FIELD(f, fmt.sliced);
			if (ops->vidioc_s_fmt_sliced_vbi_out)
				ret = ops->vidioc_s_fmt_sliced_vbi_out(file,
									fh, f);
			break;
		case V4L2_BUF_TYPE_PRIVATE:
			/* CLEAR_AFTER_FIELD(f, fmt.raw_data); <- does nothing */
			if (ops->vidioc_s_fmt_type_private)
				ret = ops->vidioc_s_fmt_type_private(file,
								fh, f);
			break;
		}
		break;
	}
	case VIDIOC_TRY_FMT:
	{
		struct v4l2_format *f = (struct v4l2_format *)arg;

		/* FIXME: Should be one dump per type */
		dbgarg(cmd, "type=%s\n", prt_names(f->type,
						v4l2_type_names));
		switch (f->type) {
		case V4L2_BUF_TYPE_VIDEO_CAPTURE:
			CLEAR_AFTER_FIELD(f, fmt.pix);
			if (ops->vidioc_try_fmt_vid_cap)
				ret = ops->vidioc_try_fmt_vid_cap(file, fh, f);
			if (!ret)
				v4l_print_pix_fmt(vfd, &f->fmt.pix);
			break;
		case V4L2_BUF_TYPE_VIDEO_OVERLAY:
			CLEAR_AFTER_FIELD(f, fmt.win);
			if (ops->vidioc_try_fmt_vid_overlay)
				ret = ops->vidioc_try_fmt_vid_overlay(file,
					fh, f);
			break;
		case V4L2_BUF_TYPE_VIDEO_OUTPUT:
			CLEAR_AFTER_FIELD(f, fmt.pix);
			if (ops->vidioc_try_fmt_vid_out)
				ret = ops->vidioc_try_fmt_vid_out(file, fh, f);
			if (!ret)
				v4l_print_pix_fmt(vfd, &f->fmt.pix);
			break;
		case V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY:
			CLEAR_AFTER_FIELD(f, fmt.win);
			if (ops->vidioc_try_fmt_vid_out_overlay)
				ret = ops->vidioc_try_fmt_vid_out_overlay(file,
				       fh, f);
			break;
		case V4L2_BUF_TYPE_VBI_CAPTURE:
			CLEAR_AFTER_FIELD(f, fmt.vbi);
			if (ops->vidioc_try_fmt_vbi_cap)
				ret = ops->vidioc_try_fmt_vbi_cap(file, fh, f);
			break;
		case V4L2_BUF_TYPE_VBI_OUTPUT:
			CLEAR_AFTER_FIELD(f, fmt.vbi);
			if (ops->vidioc_try_fmt_vbi_out)
				ret = ops->vidioc_try_fmt_vbi_out(file, fh, f);
			break;
		case V4L2_BUF_TYPE_SLICED_VBI_CAPTURE:
			CLEAR_AFTER_FIELD(f, fmt.sliced);
			if (ops->vidioc_try_fmt_sliced_vbi_cap)
				ret = ops->vidioc_try_fmt_sliced_vbi_cap(file,
								fh, f);
			break;
		case V4L2_BUF_TYPE_SLICED_VBI_OUTPUT:
			CLEAR_AFTER_FIELD(f, fmt.sliced);
			if (ops->vidioc_try_fmt_sliced_vbi_out)
				ret = ops->vidioc_try_fmt_sliced_vbi_out(file,
								fh, f);
			break;
		case V4L2_BUF_TYPE_PRIVATE:
			/* CLEAR_AFTER_FIELD(f, fmt.raw_data); <- does nothing */
			if (ops->vidioc_try_fmt_type_private)
				ret = ops->vidioc_try_fmt_type_private(file,
								fh, f);
			break;
		}

		break;
	}
	/* FIXME: Those buf reqs could be handled here,
	   with some changes on videobuf to allow its header to be included at
	   videodev2.h or being merged at videodev2.
	 */
	case VIDIOC_REQBUFS:
	{
		struct v4l2_requestbuffers *p = arg;

		if (!ops->vidioc_reqbufs)
			break;
		ret = check_fmt(ops, p->type);
		if (ret)
			break;

		if (p->type < V4L2_BUF_TYPE_PRIVATE)
			CLEAR_AFTER_FIELD(p, memory);

		ret = ops->vidioc_reqbufs(file, fh, p);
		dbgarg(cmd, "count=%d, type=%s, memory=%s\n",
				p->count,
				prt_names(p->type, v4l2_type_names),
				prt_names(p->memory, v4l2_memory_names));
		break;
	}
	case VIDIOC_QUERYBUF:
	{
		struct v4l2_buffer *p = arg;

		if (!ops->vidioc_querybuf)
			break;
		ret = check_fmt(ops, p->type);
		if (ret)
			break;

		ret = ops->vidioc_querybuf(file, fh, p);
		if (!ret)
			dbgbuf(cmd, vfd, p);
		break;
	}
	case VIDIOC_QBUF:
	{
		struct v4l2_buffer *p = arg;

		if (!ops->vidioc_qbuf)
			break;
		ret = check_fmt(ops, p->type);
		if (ret)
			break;

		ret = ops->vidioc_qbuf(file, fh, p);
		if (!ret)
			dbgbuf(cmd, vfd, p);
		break;
	}
	case VIDIOC_DQBUF:
	{
		struct v4l2_buffer *p = arg;

		if (!ops->vidioc_dqbuf)
			break;
		ret = check_fmt(ops, p->type);
		if (ret)
			break;

		ret = ops->vidioc_dqbuf(file, fh, p);
		if (!ret)
			dbgbuf(cmd, vfd, p);
		break;
	}
	case VIDIOC_OVERLAY:
	{
		int *i = arg;

		if (!ops->vidioc_overlay)
			break;
		dbgarg(cmd, "value=%d\n", *i);
		ret = ops->vidioc_overlay(file, fh, *i);
		break;
	}
	case VIDIOC_G_FBUF:
	{
		struct v4l2_framebuffer *p = arg;

		if (!ops->vidioc_g_fbuf)
			break;
		ret = ops->vidioc_g_fbuf(file, fh, arg);
		if (!ret) {
			dbgarg(cmd, "capability=0x%x, flags=%d, base=0x%08lx\n",
					p->capability, p->flags,
					(unsigned long)p->base);
			v4l_print_pix_fmt(vfd, &p->fmt);
		}
		break;
	}
	case VIDIOC_S_FBUF:
	{
		struct v4l2_framebuffer *p = arg;

		if (!ops->vidioc_s_fbuf)
			break;
		dbgarg(cmd, "capability=0x%x, flags=%d, base=0x%08lx\n",
			p->capability, p->flags, (unsigned long)p->base);
		v4l_print_pix_fmt(vfd, &p->fmt);
		ret = ops->vidioc_s_fbuf(file, fh, arg);
		break;
	}
	case VIDIOC_STREAMON:
	{
		enum v4l2_buf_type i = *(int *)arg;

		if (!ops->vidioc_streamon)
			break;
		dbgarg(cmd, "type=%s\n", prt_names(i, v4l2_type_names));
		ret = ops->vidioc_streamon(file, fh, i);
		break;
	}
	case VIDIOC_STREAMOFF:
	{
		enum v4l2_buf_type i = *(int *)arg;

		if (!ops->vidioc_streamoff)
			break;
		dbgarg(cmd, "type=%s\n", prt_names(i, v4l2_type_names));
		ret = ops->vidioc_streamoff(file, fh, i);
		break;
	}
	/* ---------- tv norms ---------- */
	case VIDIOC_ENUMSTD:
	{
		struct v4l2_standard *p = arg;
		v4l2_std_id id = vfd->tvnorms, curr_id = 0;
		unsigned int index = p->index, i, j = 0;
		const char *descr = "";

		/* Return norm array in a canonical way */
		for (i = 0; i <= index && id; i++) {
			/* last std value in the standards array is 0, so this
			   while always ends there since (id & 0) == 0. */
			while ((id & standards[j].std) != standards[j].std)
				j++;
			curr_id = standards[j].std;
			descr = standards[j].descr;
			j++;
			if (curr_id == 0)
				break;
			if (curr_id != V4L2_STD_PAL &&
			    curr_id != V4L2_STD_SECAM &&
			    curr_id != V4L2_STD_NTSC)
				id &= ~curr_id;
		}
		if (i <= index)
			break;

		v4l2_video_std_construct(p, curr_id, descr);

		dbgarg(cmd, "index=%d, id=0x%Lx, name=%s, fps=%d/%d, "
				"framelines=%d\n", p->index,
				(unsigned long long)p->id, p->name,
				p->frameperiod.numerator,
				p->frameperiod.denominator,
				p->framelines);

		ret = 0;
		break;
	}
	case VIDIOC_G_STD:
	{
		v4l2_std_id *id = arg;

		ret = 0;
		/* Calls the specific handler */
		if (ops->vidioc_g_std)
			ret = ops->vidioc_g_std(file, fh, id);
		else if (vfd->current_norm)
			*id = vfd->current_norm;
		else
			ret = -EINVAL;

		if (!ret)
			dbgarg(cmd, "std=0x%08Lx\n", (long long unsigned)*id);
		break;
	}
	case VIDIOC_S_STD:
	{
		v4l2_std_id *id = arg, norm;

		dbgarg(cmd, "std=%08Lx\n", (long long unsigned)*id);

		norm = (*id) & vfd->tvnorms;
		if (vfd->tvnorms && !norm)	/* Check if std is supported */
			break;

		/* Calls the specific handler */
		if (ops->vidioc_s_std)
			ret = ops->vidioc_s_std(file, fh, &norm);
		else
			ret = -EINVAL;

		/* Updates standard information */
		if (ret >= 0)
			vfd->current_norm = norm;
		break;
	}
	case VIDIOC_QUERYSTD:
	{
		v4l2_std_id *p = arg;

		if (!ops->vidioc_querystd)
			break;
		ret = ops->vidioc_querystd(file, fh, arg);
		if (!ret)
			dbgarg(cmd, "detected std=%08Lx\n",
						(unsigned long long)*p);
		break;
	}
	/* ------ input switching ---------- */
	/* FIXME: Inputs can be handled inside videodev2 */
	case VIDIOC_ENUMINPUT:
	{
		struct v4l2_input *p = arg;

		/*
		 * We set the flags for CAP_PRESETS, CAP_CUSTOM_TIMINGS &
		 * CAP_STD here based on ioctl handler provided by the
		 * driver. If the driver doesn't support these
		 * for a specific input, it must override these flags.
		 */
		if (ops->vidioc_s_std)
			p->capabilities |= V4L2_IN_CAP_STD;
		if (ops->vidioc_s_dv_preset)
			p->capabilities |= V4L2_IN_CAP_PRESETS;
		if (ops->vidioc_s_dv_timings)
			p->capabilities |= V4L2_IN_CAP_CUSTOM_TIMINGS;

		if (!ops->vidioc_enum_input)
			break;

		ret = ops->vidioc_enum_input(file, fh, p);
		if (!ret)
			dbgarg(cmd, "index=%d, name=%s, type=%d, "
				"audioset=%d, "
				"tuner=%d, std=%08Lx, status=%d\n",
				p->index, p->name, p->type, p->audioset,
				p->tuner,
				(unsigned long long)p->std,
				p->status);
		break;
	}
	case VIDIOC_G_INPUT:
	{
		unsigned int *i = arg;

		if (!ops->vidioc_g_input)
			break;
		ret = ops->vidioc_g_input(file, fh, i);
		if (!ret)
			dbgarg(cmd, "value=%d\n", *i);
		break;
	}
	case VIDIOC_S_INPUT:
	{
		unsigned int *i = arg;

		if (!ops->vidioc_s_input)
			break;
		dbgarg(cmd, "value=%d\n", *i);
		ret = ops->vidioc_s_input(file, fh, *i);
		break;
	}

	/* ------ output switching ---------- */
	case VIDIOC_ENUMOUTPUT:
	{
		struct v4l2_output *p = arg;

		if (!ops->vidioc_enum_output)
			break;

		/*
		 * We set the flags for CAP_PRESETS, CAP_CUSTOM_TIMINGS &
		 * CAP_STD here based on ioctl handler provided by the
		 * driver. If the driver doesn't support these
		 * for a specific output, it must override these flags.
		 */
		if (ops->vidioc_s_std)
			p->capabilities |= V4L2_OUT_CAP_STD;
		if (ops->vidioc_s_dv_preset)
			p->capabilities |= V4L2_OUT_CAP_PRESETS;
		if (ops->vidioc_s_dv_timings)
			p->capabilities |= V4L2_OUT_CAP_CUSTOM_TIMINGS;

		ret = ops->vidioc_enum_output(file, fh, p);
		if (!ret)
			dbgarg(cmd, "index=%d, name=%s, type=%d, "
				"audioset=0x%x, "
				"modulator=%d, std=0x%08Lx\n",
				p->index, p->name, p->type, p->audioset,
				p->modulator, (unsigned long long)p->std);
		break;
	}
	case VIDIOC_G_OUTPUT:
	{
		unsigned int *i = arg;

		if (!ops->vidioc_g_output)
			break;
		ret = ops->vidioc_g_output(file, fh, i);
		if (!ret)
			dbgarg(cmd, "value=%d\n", *i);
		break;
	}
	case VIDIOC_S_OUTPUT:
	{
		unsigned int *i = arg;

		if (!ops->vidioc_s_output)
			break;
		dbgarg(cmd, "value=%d\n", *i);
		ret = ops->vidioc_s_output(file, fh, *i);
		break;
	}

	/* --- controls ---------------------------------------------- */
	case VIDIOC_QUERYCTRL:
	{
		struct v4l2_queryctrl *p = arg;

		if (shvfd->ctrl_handler)
			ret = v4l2_queryctrl(shvfd->ctrl_handler, p);
		else if (ops->vidioc_queryctrl)
			ret = ops->vidioc_queryctrl(file, fh, p);
		else
			break;
		if (!ret)
			dbgarg(cmd, "id=0x%x, type=%d, name=%s, min/max=%d/%d, "
					"step=%d, default=%d, flags=0x%08x\n",
					p->id, p->type, p->name,
					p->minimum, p->maximum,
					p->step, p->default_value, p->flags);
		else
			dbgarg(cmd, "id=0x%x\n", p->id);
		break;
	}
	case VIDIOC_G_CTRL:
	{
		struct v4l2_control *p = arg;

		if (shvfd->ctrl_handler)
			ret = v4l2_g_ctrl(shvfd->ctrl_handler, p);
		else if (ops->vidioc_g_ctrl)
			ret = ops->vidioc_g_ctrl(file, fh, p);
		else if (ops->vidioc_g_ext_ctrls) {
			struct v4l2_ext_controls ctrls;
			struct v4l2_ext_control ctrl;

			ctrls.ctrl_class = V4L2_CTRL_ID2CLASS(p->id);
			ctrls.count = 1;
			ctrls.controls = &ctrl;
			ctrl.id = p->id;
			ctrl.value = p->value;
			if (check_ext_ctrls(&ctrls, 1)) {
				ret = ops->vidioc_g_ext_ctrls(file, fh, &ctrls);
				if (ret == 0)
					p->value = ctrl.value;
			}
		} else
			break;
		if (!ret)
			dbgarg(cmd, "id=0x%x, value=%d\n", p->id, p->value);
		else
			dbgarg(cmd, "id=0x%x\n", p->id);
		break;
	}
	case VIDIOC_S_CTRL:
	{
		struct v4l2_control *p = arg;
		struct v4l2_ext_controls ctrls;
		struct v4l2_ext_control ctrl;

		if (!shvfd->ctrl_handler &&
			!ops->vidioc_s_ctrl && !ops->vidioc_s_ext_ctrls)
			break;

		dbgarg(cmd, "id=0x%x, value=%d\n", p->id, p->value);

		if (shvfd->ctrl_handler) {
			ret = v4l2_s_ctrl(shvfd->ctrl_handler, p);
			break;
		}
		if (ops->vidioc_s_ctrl) {
			ret = ops->vidioc_s_ctrl(file, fh, p);
			break;
		}
		if (!ops->vidioc_s_ext_ctrls)
			break;

		ctrls.ctrl_class = V4L2_CTRL_ID2CLASS(p->id);
		ctrls.count = 1;
		ctrls.controls = &ctrl;
		ctrl.id = p->id;
		ctrl.value = p->value;
		if (check_ext_ctrls(&ctrls, 1))
			ret = ops->vidioc_s_ext_ctrls(file, fh, &ctrls);
		break;
	}
	case VIDIOC_G_EXT_CTRLS:
	{
		struct v4l2_ext_controls *p = arg;

		p->error_idx = p->count;
		if (shvfd->ctrl_handler)
			ret = v4l2_g_ext_ctrls(shvfd->ctrl_handler, p);
		else if (ops->vidioc_g_ext_ctrls && check_ext_ctrls(p, 0))
			ret = ops->vidioc_g_ext_ctrls(file, fh, p);
		else
			break;
		v4l_print_ext_ctrls(cmd, vfd, p, !ret);
		break;
	}
	case VIDIOC_S_EXT_CTRLS:
	{
		struct v4l2_ext_controls *p = arg;

		p->error_idx = p->count;
		if (!shvfd->ctrl_handler && !ops->vidioc_s_ext_ctrls)
			break;
		v4l_print_ext_ctrls(cmd, vfd, p, 1);
		if (shvfd->ctrl_handler)
			ret = v4l2_s_ext_ctrls(shvfd->ctrl_handler, p);
		else if (check_ext_ctrls(p, 0))
			ret = ops->vidioc_s_ext_ctrls(file, fh, p);
		break;
	}
	case VIDIOC_TRY_EXT_CTRLS:
	{
		struct v4l2_ext_controls *p = arg;

		p->error_idx = p->count;
		if (!shvfd->ctrl_handler && !ops->vidioc_try_ext_ctrls)
			break;
		v4l_print_ext_ctrls(cmd, vfd, p, 1);
		if (shvfd->ctrl_handler)
			ret = v4l2_try_ext_ctrls(shvfd->ctrl_handler, p);
		else if (check_ext_ctrls(p, 0))
			ret = ops->vidioc_try_ext_ctrls(file, fh, p);
		break;
	}
	case VIDIOC_QUERYMENU:
	{
		struct v4l2_querymenu *p = arg;

		if (shvfd->ctrl_handler)
			ret = v4l2_querymenu(shvfd->ctrl_handler, p);
		else if (ops->vidioc_querymenu)
			ret = ops->vidioc_querymenu(file, fh, p);
		else
			break;
		if (!ret)
			dbgarg(cmd, "id=0x%x, index=%d, name=%s\n",
				p->id, p->index, p->name);
		else
			dbgarg(cmd, "id=0x%x, index=%d\n",
				p->id, p->index);
		break;
	}
	/* --- audio ---------------------------------------------- */
	case VIDIOC_ENUMAUDIO:
	{
		struct v4l2_audio *p = arg;

		if (!ops->vidioc_enumaudio)
			break;
		ret = ops->vidioc_enumaudio(file, fh, p);
		if (!ret)
			dbgarg(cmd, "index=%d, name=%s, capability=0x%x, "
					"mode=0x%x\n", p->index, p->name,
					p->capability, p->mode);
		else
			dbgarg(cmd, "index=%d\n", p->index);
		break;
	}
	case VIDIOC_G_AUDIO:
	{
		struct v4l2_audio *p = arg;

		if (!ops->vidioc_g_audio)
			break;

		ret = ops->vidioc_g_audio(file, fh, p);
		if (!ret)
			dbgarg(cmd, "index=%d, name=%s, capability=0x%x, "
					"mode=0x%x\n", p->index,
					p->name, p->capability, p->mode);
		else
			dbgarg(cmd, "index=%d\n", p->index);
		break;
	}
	case VIDIOC_S_AUDIO:
	{
		struct v4l2_audio *p = arg;

		if (!ops->vidioc_s_audio)
			break;
		dbgarg(cmd, "index=%d, name=%s, capability=0x%x, "
					"mode=0x%x\n", p->index, p->name,
					p->capability, p->mode);
		ret = ops->vidioc_s_audio(file, fh, p);
		break;
	}
	case VIDIOC_ENUMAUDOUT:
	{
		struct v4l2_audioout *p = arg;

		if (!ops->vidioc_enumaudout)
			break;
		dbgarg(cmd, "Enum for index=%d\n", p->index);
		ret = ops->vidioc_enumaudout(file, fh, p);
		if (!ret)
			dbgarg2("index=%d, name=%s, capability=%d, "
					"mode=%d\n", p->index, p->name,
					p->capability, p->mode);
		break;
	}
	case VIDIOC_G_AUDOUT:
	{
		struct v4l2_audioout *p = arg;

		if (!ops->vidioc_g_audout)
			break;

		ret = ops->vidioc_g_audout(file, fh, p);
		if (!ret)
			dbgarg2("index=%d, name=%s, capability=%d, "
					"mode=%d\n", p->index, p->name,
					p->capability, p->mode);
		break;
	}
	case VIDIOC_S_AUDOUT:
	{
		struct v4l2_audioout *p = arg;

		if (!ops->vidioc_s_audout)
			break;
		dbgarg(cmd, "index=%d, name=%s, capability=%d, "
					"mode=%d\n", p->index, p->name,
					p->capability, p->mode);

		ret = ops->vidioc_s_audout(file, fh, p);
		break;
	}
	case VIDIOC_G_MODULATOR:
	{
		struct v4l2_modulator *p = arg;

		if (!ops->vidioc_g_modulator)
			break;
		ret = ops->vidioc_g_modulator(file, fh, p);
		if (!ret)
			dbgarg(cmd, "index=%d, name=%s, "
					"capability=%d, rangelow=%d,"
					" rangehigh=%d, txsubchans=%d\n",
					p->index, p->name, p->capability,
					p->rangelow, p->rangehigh,
					p->txsubchans);
		break;
	}
	case VIDIOC_S_MODULATOR:
	{
		struct v4l2_modulator *p = arg;

		if (!ops->vidioc_s_modulator)
			break;
		dbgarg(cmd, "index=%d, name=%s, capability=%d, "
				"rangelow=%d, rangehigh=%d, txsubchans=%d\n",
				p->index, p->name, p->capability, p->rangelow,
				p->rangehigh, p->txsubchans);
			ret = ops->vidioc_s_modulator(file, fh, p);
		break;
	}
	case VIDIOC_G_CROP:
	{
		struct v4l2_crop *p = arg;

		if (!ops->vidioc_g_crop)
			break;

		dbgarg(cmd, "type=%s\n", prt_names(p->type, v4l2_type_names));
		ret = ops->vidioc_g_crop(file, fh, p);
		if (!ret)
			dbgrect(vfd, "", &p->c);
		break;
	}
	case VIDIOC_S_CROP:
	{
		struct v4l2_crop *p = arg;

		if (!ops->vidioc_s_crop)
			break;
		dbgarg(cmd, "type=%s\n", prt_names(p->type, v4l2_type_names));
		dbgrect(vfd, "", &p->c);
		ret = ops->vidioc_s_crop(file, fh, p);
		break;
	}
	case VIDIOC_CROPCAP:
	{
		struct v4l2_cropcap *p = arg;

		/*FIXME: Should also show v4l2_fract pixelaspect */
		if (!ops->vidioc_cropcap)
			break;

		dbgarg(cmd, "type=%s\n", prt_names(p->type, v4l2_type_names));
		ret = ops->vidioc_cropcap(file, fh, p);
		if (!ret) {
			dbgrect(vfd, "bounds ", &p->bounds);
			dbgrect(vfd, "defrect ", &p->defrect);
		}
		break;
	}
	case VIDIOC_G_JPEGCOMP:
	{
		struct v4l2_jpegcompression *p = arg;

		if (!ops->vidioc_g_jpegcomp)
			break;

		ret = ops->vidioc_g_jpegcomp(file, fh, p);
		if (!ret)
			dbgarg(cmd, "quality=%d, APPn=%d, "
					"APP_len=%d, COM_len=%d, "
					"jpeg_markers=%d\n",
					p->quality, p->APPn, p->APP_len,
					p->COM_len, p->jpeg_markers);
		break;
	}
	case VIDIOC_S_JPEGCOMP:
	{
		struct v4l2_jpegcompression *p = arg;

		if (!ops->vidioc_g_jpegcomp)
			break;
		dbgarg(cmd, "quality=%d, APPn=%d, APP_len=%d, "
					"COM_len=%d, jpeg_markers=%d\n",
					p->quality, p->APPn, p->APP_len,
					p->COM_len, p->jpeg_markers);
			ret = ops->vidioc_s_jpegcomp(file, fh, p);
		break;
	}
	case VIDIOC_G_ENC_INDEX:
	{
		struct v4l2_enc_idx *p = arg;

		if (!ops->vidioc_g_enc_index)
			break;
		ret = ops->vidioc_g_enc_index(file, fh, p);
		if (!ret)
			dbgarg(cmd, "entries=%d, entries_cap=%d\n",
					p->entries, p->entries_cap);
		break;
	}
	case VIDIOC_ENCODER_CMD:
	{
		struct v4l2_encoder_cmd *p = arg;

		if (!ops->vidioc_encoder_cmd)
			break;
		ret = ops->vidioc_encoder_cmd(file, fh, p);
		if (!ret)
			dbgarg(cmd, "cmd=%d, flags=%x\n", p->cmd, p->flags);
		break;
	}
	case VIDIOC_TRY_ENCODER_CMD:
	{
		struct v4l2_encoder_cmd *p = arg;

		if (!ops->vidioc_try_encoder_cmd)
			break;
		ret = ops->vidioc_try_encoder_cmd(file, fh, p);
		if (!ret)
			dbgarg(cmd, "cmd=%d, flags=%x\n", p->cmd, p->flags);
		break;
	}
	case VIDIOC_G_PARM:
	{
		struct v4l2_streamparm *p = arg;

		if (ops->vidioc_g_parm) {
			ret = check_fmt(ops, p->type);
			if (ret)
				break;
			ret = ops->vidioc_g_parm(file, fh, p);
		} else {
			v4l2_std_id std = vfd->current_norm;

			if (p->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
				break;

			ret = 0;
			if (ops->vidioc_g_std)
				ret = ops->vidioc_g_std(file, fh, &std);
			else if (std == 0)
				ret = -EINVAL;
			if (ret == 0)
				v4l2_video_std_frame_period(std,
						    &p->parm.capture.timeperframe);
		}

		dbgarg(cmd, "type=%d\n", p->type);
		break;
	}
	case VIDIOC_S_PARM:
	{
		struct v4l2_streamparm *p = arg;

		if (!ops->vidioc_s_parm)
			break;
		ret = check_fmt(ops, p->type);
		if (ret)
			break;

		dbgarg(cmd, "type=%d\n", p->type);
		ret = ops->vidioc_s_parm(file, fh, p);
		break;
	}
	case VIDIOC_G_TUNER:
	{
		struct v4l2_tuner *p = arg;

		if (!ops->vidioc_g_tuner)
			break;

		ret = ops->vidioc_g_tuner(file, fh, p);
		if (!ret)
			dbgarg(cmd, "index=%d, name=%s, type=%d, "
					"capability=0x%x, rangelow=%d, "
					"rangehigh=%d, signal=%d, afc=%d, "
					"rxsubchans=0x%x, audmode=%d\n",
					p->index, p->name, p->type,
					p->capability, p->rangelow,
					p->rangehigh, p->signal, p->afc,
					p->rxsubchans, p->audmode);
		break;
	}
	case VIDIOC_S_TUNER:
	{
		struct v4l2_tuner *p = arg;

		if (!ops->vidioc_s_tuner)
			break;
		dbgarg(cmd, "index=%d, name=%s, type=%d, "
				"capability=0x%x, rangelow=%d, "
				"rangehigh=%d, signal=%d, afc=%d, "
				"rxsubchans=0x%x, audmode=%d\n",
				p->index, p->name, p->type,
				p->capability, p->rangelow,
				p->rangehigh, p->signal, p->afc,
				p->rxsubchans, p->audmode);
		ret = ops->vidioc_s_tuner(file, fh, p);
		break;
	}
	case VIDIOC_G_FREQUENCY:
	{
		struct v4l2_frequency *p = arg;

		if (!ops->vidioc_g_frequency)
			break;

		ret = ops->vidioc_g_frequency(file, fh, p);
		if (!ret)
			dbgarg(cmd, "tuner=%d, type=%d, frequency=%d\n",
					p->tuner, p->type, p->frequency);
		break;
	}
	case VIDIOC_S_FREQUENCY:
	{
		struct v4l2_frequency *p = arg;

		if (!ops->vidioc_s_frequency)
			break;
		dbgarg(cmd, "tuner=%d, type=%d, frequency=%d\n",
				p->tuner, p->type, p->frequency);
		ret = ops->vidioc_s_frequency(file, fh, p);
		break;
	}
	case VIDIOC_G_SLICED_VBI_CAP:
	{
		struct v4l2_sliced_vbi_cap *p = arg;

		if (!ops->vidioc_g_sliced_vbi_cap)
			break;

		/* Clear up to type, everything after type is zerod already */
		memset(p, 0, offsetof(struct v4l2_sliced_vbi_cap, type));

		dbgarg(cmd, "type=%s\n", prt_names(p->type, v4l2_type_names));
		ret = ops->vidioc_g_sliced_vbi_cap(file, fh, p);
		if (!ret)
			dbgarg2("service_set=%d\n", p->service_set);
		break;
	}
	case VIDIOC_LOG_STATUS:
	{
		if (!ops->vidioc_log_status)
			break;
		ret = ops->vidioc_log_status(file, fh);
		break;
	}
#ifdef CONFIG_VIDEO_ADV_DEBUG
	case VIDIOC_DBG_G_REGISTER:
	{
		struct v4l2_dbg_register *p = arg;

		if (ops->vidioc_g_register) {
			if (!capable(CAP_SYS_ADMIN))
				ret = -EPERM;
			else
				ret = ops->vidioc_g_register(file, fh, p);
		}
		break;
	}
	case VIDIOC_DBG_S_REGISTER:
	{
		struct v4l2_dbg_register *p = arg;

		if (ops->vidioc_s_register) {
			if (!capable(CAP_SYS_ADMIN))
				ret = -EPERM;
			else
				ret = ops->vidioc_s_register(file, fh, p);
		}
		break;
	}
#endif
	case VIDIOC_DBG_G_CHIP_IDENT:
	{
		struct v4l2_dbg_chip_ident *p = arg;

		if (!ops->vidioc_g_chip_ident)
			break;
		p->ident = V4L2_IDENT_NONE;
		p->revision = 0;
		ret = ops->vidioc_g_chip_ident(file, fh, p);
		if (!ret)
			dbgarg(cmd, "chip_ident=%u, revision=0x%x\n", p->ident, p->revision);
		break;
	}
	case VIDIOC_S_HW_FREQ_SEEK:
	{
		struct v4l2_hw_freq_seek *p = arg;

		if (!ops->vidioc_s_hw_freq_seek)
			break;
		dbgarg(cmd,
			"tuner=%d, type=%d, seek_upward=%d, wrap_around=%d\n",
			p->tuner, p->type, p->seek_upward, p->wrap_around);
		ret = ops->vidioc_s_hw_freq_seek(file, fh, p);
		break;
	}
	case VIDIOC_ENUM_FRAMESIZES:
	{
		struct v4l2_frmsizeenum *p = arg;

		if (!ops->vidioc_enum_framesizes)
			break;

		ret = ops->vidioc_enum_framesizes(file, fh, p);
		dbgarg(cmd,
			"index=%d, pixelformat=%c%c%c%c, type=%d ",
			p->index,
			(p->pixel_format & 0xff),
			(p->pixel_format >>  8) & 0xff,
			(p->pixel_format >> 16) & 0xff,
			(p->pixel_format >> 24) & 0xff,
			p->type);
		switch (p->type) {
		case V4L2_FRMSIZE_TYPE_DISCRETE:
			dbgarg3("width = %d, height=%d\n",
				p->discrete.width, p->discrete.height);
			break;
		case V4L2_FRMSIZE_TYPE_STEPWISE:
			dbgarg3("min %dx%d, max %dx%d, step %dx%d\n",
				p->stepwise.min_width,  p->stepwise.min_height,
				p->stepwise.step_width, p->stepwise.step_height,
				p->stepwise.max_width,  p->stepwise.max_height);
			break;
		case V4L2_FRMSIZE_TYPE_CONTINUOUS:
			dbgarg3("continuous\n");
			break;
		default:
			dbgarg3("- Unknown type!\n");
		}

		break;
	}
	case VIDIOC_ENUM_FRAMEINTERVALS:
	{
		struct v4l2_frmivalenum *p = arg;

		if (!ops->vidioc_enum_frameintervals)
			break;

		ret = ops->vidioc_enum_frameintervals(file, fh, p);
		dbgarg(cmd,
			"index=%d, pixelformat=%d, width=%d, height=%d, type=%d ",
			p->index, p->pixel_format,
			p->width, p->height, p->type);
		switch (p->type) {
		case V4L2_FRMIVAL_TYPE_DISCRETE:
			dbgarg2("fps=%d/%d\n",
				p->discrete.numerator,
				p->discrete.denominator);
			break;
		case V4L2_FRMIVAL_TYPE_STEPWISE:
			dbgarg2("min=%d/%d, max=%d/%d, step=%d/%d\n",
				p->stepwise.min.numerator,
				p->stepwise.min.denominator,
				p->stepwise.max.numerator,
				p->stepwise.max.denominator,
				p->stepwise.step.numerator,
				p->stepwise.step.denominator);
			break;
		case V4L2_FRMIVAL_TYPE_CONTINUOUS:
			dbgarg2("continuous\n");
			break;
		default:
			dbgarg2("- Unknown type!\n");
		}
		break;
	}
	case VIDIOC_ENUM_DV_PRESETS:
	{
		struct v4l2_dv_enum_preset *p = arg;

		if (!ops->vidioc_enum_dv_presets)
			break;

		ret = ops->vidioc_enum_dv_presets(file, fh, p);
		if (!ret)
			dbgarg(cmd,
				"index=%d, preset=%d, name=%s, width=%d,"
				" height=%d ",
				p->index, p->preset, p->name, p->width,
				p->height);
		break;
	}
	case VIDIOC_S_DV_PRESET:
	{
		struct v4l2_dv_preset *p = arg;

		if (!ops->vidioc_s_dv_preset)
			break;

		dbgarg(cmd, "preset=%d\n", p->preset);
		ret = ops->vidioc_s_dv_preset(file, fh, p);
		break;
	}
	case VIDIOC_G_DV_PRESET:
	{
		struct v4l2_dv_preset *p = arg;

		if (!ops->vidioc_g_dv_preset)
			break;

		ret = ops->vidioc_g_dv_preset(file, fh, p);
		if (!ret)
			dbgarg(cmd, "preset=%d\n", p->preset);
		break;
	}
	case VIDIOC_QUERY_DV_PRESET:
	{
		struct v4l2_dv_preset *p = arg;

		if (!ops->vidioc_query_dv_preset)
			break;

		ret = ops->vidioc_query_dv_preset(file, fh, p);
		if (!ret)
			dbgarg(cmd, "preset=%d\n", p->preset);
		break;
	}
	case VIDIOC_S_DV_TIMINGS:
	{
		struct v4l2_dv_timings *p = arg;

		if (!ops->vidioc_s_dv_timings)
			break;

		switch (p->type) {
		case V4L2_DV_BT_656_1120:
			dbgarg2("bt-656/1120:interlaced=%d, pixelclock=%lld,"
				" width=%d, height=%d, polarities=%x,"
				" hfrontporch=%d, hsync=%d, hbackporch=%d,"
				" vfrontporch=%d, vsync=%d, vbackporch=%d,"
				" il_vfrontporch=%d, il_vsync=%d,"
				" il_vbackporch=%d\n",
				p->bt.interlaced, p->bt.pixelclock,
				p->bt.width, p->bt.height, p->bt.polarities,
				p->bt.hfrontporch, p->bt.hsync,
				p->bt.hbackporch, p->bt.vfrontporch,
				p->bt.vsync, p->bt.vbackporch,
				p->bt.il_vfrontporch, p->bt.il_vsync,
				p->bt.il_vbackporch);
			ret = ops->vidioc_s_dv_timings(file, fh, p);
			break;
		default:
			dbgarg2("Unknown type %d!\n", p->type);
			break;
		}
		break;
	}
	case VIDIOC_G_DV_TIMINGS:
	{
		struct v4l2_dv_timings *p = arg;

		if (!ops->vidioc_g_dv_timings)
			break;

		ret = ops->vidioc_g_dv_timings(file, fh, p);
		if (!ret) {
			switch (p->type) {
			case V4L2_DV_BT_656_1120:
				dbgarg2("bt-656/1120:interlaced=%d,"
					" pixelclock=%lld,"
					" width=%d, height=%d, polarities=%x,"
					" hfrontporch=%d, hsync=%d,"
					" hbackporch=%d, vfrontporch=%d,"
					" vsync=%d, vbackporch=%d,"
					" il_vfrontporch=%d, il_vsync=%d,"
					" il_vbackporch=%d\n",
					p->bt.interlaced, p->bt.pixelclock,
					p->bt.width, p->bt.height,
					p->bt.polarities, p->bt.hfrontporch,
					p->bt.hsync, p->bt.hbackporch,
					p->bt.vfrontporch, p->bt.vsync,
					p->bt.vbackporch, p->bt.il_vfrontporch,
					p->bt.il_vsync, p->bt.il_vbackporch);
				break;
			default:
				dbgarg2("Unknown type %d!\n", p->type);
				break;
			}
		}
		break;
	}
	case VIDIOC_DQEVENT:
	{
		struct v4l2_event *ev = arg;

		if (!ops->vidioc_subscribe_event)
			break;

		ret = v4l2_event_dequeue(fh, ev, file->f_flags & O_NONBLOCK);
		if (ret < 0) {
			dbgarg(cmd, "no pending events?");
			break;
		}
		dbgarg(cmd,
		       "pending=%d, type=0x%8.8x, sequence=%d, "
		       "timestamp=%lu.%9.9lu ",
		       ev->pending, ev->type, ev->sequence,
		       ev->timestamp.tv_sec, ev->timestamp.tv_nsec);
		break;
	}
	case VIDIOC_SUBSCRIBE_EVENT:
	{
		struct v4l2_event_subscription *sub = arg;

		if (!ops->vidioc_subscribe_event)
			break;

		ret = ops->vidioc_subscribe_event(fh, sub);
		if (ret < 0) {
			dbgarg(cmd, "failed, ret=%ld", ret);
			break;
		}
		dbgarg(cmd, "type=0x%8.8x", sub->type);
		break;
	}
	case VIDIOC_UNSUBSCRIBE_EVENT:
	{
		struct v4l2_event_subscription *sub = arg;

		if (!ops->vidioc_unsubscribe_event)
			break;

		ret = ops->vidioc_unsubscribe_event(fh, sub);
		if (ret < 0) {
			dbgarg(cmd, "failed, ret=%ld", ret);
			break;
		}
		dbgarg(cmd, "type=0x%8.8x", sub->type);
		break;
	}
	default:
	{
		if (!ops->vidioc_default)
			break;
		ret = ops->vidioc_default(file, fh, cmd, arg);
		break;
	}
	}
