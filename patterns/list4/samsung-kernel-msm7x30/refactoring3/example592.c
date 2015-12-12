switch (cmd) {
	case VIDIOC_QUERYCAP:
	{
		struct v4l2_capability *cap = arg;

		memcpy(cap, &pvr_capability, sizeof(struct v4l2_capability));
		strlcpy(cap->bus_info,pvr2_hdw_get_bus_info(hdw),
			sizeof(cap->bus_info));
		strlcpy(cap->card,pvr2_hdw_get_desc(hdw),sizeof(cap->card));

		ret = 0;
		break;
	}

	case VIDIOC_G_PRIORITY:
	{
		enum v4l2_priority *p = arg;

		*p = v4l2_prio_max(&vp->prio);
		ret = 0;
		break;
	}

	case VIDIOC_S_PRIORITY:
	{
		enum v4l2_priority *prio = arg;

		ret = v4l2_prio_change(&vp->prio, &fh->prio, *prio);
		break;
	}

	case VIDIOC_ENUMSTD:
	{
		struct v4l2_standard *vs = (struct v4l2_standard *)arg;
		int idx = vs->index;
		ret = pvr2_hdw_get_stdenum_value(hdw,vs,idx+1);
		break;
	}

	case VIDIOC_QUERYSTD:
	{
		v4l2_std_id *std = arg;
		*std = V4L2_STD_ALL;
		ret = pvr2_hdw_get_detected_std(hdw, std);
		break;
	}

	case VIDIOC_G_STD:
	{
		int val = 0;
		ret = pvr2_ctrl_get_value(
			pvr2_hdw_get_ctrl_by_id(hdw,PVR2_CID_STDCUR),&val);
		*(v4l2_std_id *)arg = val;
		break;
	}

	case VIDIOC_S_STD:
	{
		ret = pvr2_ctrl_set_value(
			pvr2_hdw_get_ctrl_by_id(hdw,PVR2_CID_STDCUR),
			*(v4l2_std_id *)arg);
		break;
	}

	case VIDIOC_ENUMINPUT:
	{
		struct pvr2_ctrl *cptr;
		struct v4l2_input *vi = (struct v4l2_input *)arg;
		struct v4l2_input tmp;
		unsigned int cnt;
		int val;

		cptr = pvr2_hdw_get_ctrl_by_id(hdw,PVR2_CID_INPUT);

		memset(&tmp,0,sizeof(tmp));
		tmp.index = vi->index;
		ret = 0;
		if (vi->index >= fh->input_cnt) {
			ret = -EINVAL;
			break;
		}
		val = fh->input_map[vi->index];
		switch (val) {
		case PVR2_CVAL_INPUT_TV:
		case PVR2_CVAL_INPUT_DTV:
		case PVR2_CVAL_INPUT_RADIO:
			tmp.type = V4L2_INPUT_TYPE_TUNER;
			break;
		case PVR2_CVAL_INPUT_SVIDEO:
		case PVR2_CVAL_INPUT_COMPOSITE:
			tmp.type = V4L2_INPUT_TYPE_CAMERA;
			break;
		default:
			ret = -EINVAL;
			break;
		}
		if (ret < 0) break;

		cnt = 0;
		pvr2_ctrl_get_valname(cptr,val,
				      tmp.name,sizeof(tmp.name)-1,&cnt);
		tmp.name[cnt] = 0;

		/* Don't bother with audioset, since this driver currently
		   always switches the audio whenever the video is
		   switched. */

		/* Handling std is a tougher problem.  It doesn't make
		   sense in cases where a device might be multi-standard.
		   We could just copy out the current value for the
		   standard, but it can change over time.  For now just
		   leave it zero. */

		memcpy(vi, &tmp, sizeof(tmp));

		ret = 0;
		break;
	}

	case VIDIOC_G_INPUT:
	{
		unsigned int idx;
		struct pvr2_ctrl *cptr;
		struct v4l2_input *vi = (struct v4l2_input *)arg;
		int val;
		cptr = pvr2_hdw_get_ctrl_by_id(hdw,PVR2_CID_INPUT);
		val = 0;
		ret = pvr2_ctrl_get_value(cptr,&val);
		vi->index = 0;
		for (idx = 0; idx < fh->input_cnt; idx++) {
			if (fh->input_map[idx] == val) {
				vi->index = idx;
				break;
			}
		}
		break;
	}

	case VIDIOC_S_INPUT:
	{
		struct v4l2_input *vi = (struct v4l2_input *)arg;
		if (vi->index >= fh->input_cnt) {
			ret = -ERANGE;
			break;
		}
		ret = pvr2_ctrl_set_value(
			pvr2_hdw_get_ctrl_by_id(hdw,PVR2_CID_INPUT),
			fh->input_map[vi->index]);
		break;
	}

	case VIDIOC_ENUMAUDIO:
	{
		/* pkt: FIXME: We are returning one "fake" input here
		   which could very well be called "whatever_we_like".
		   This is for apps that want to see an audio input
		   just to feel comfortable, as well as to test if
		   it can do stereo or sth. There is actually no guarantee
		   that the actual audio input cannot change behind the app's
		   back, but most applications should not mind that either.

		   Hopefully, mplayer people will work with us on this (this
		   whole mess is to support mplayer pvr://), or Hans will come
		   up with a more standard way to say "we have inputs but we
		   don 't want you to change them independent of video" which
		   will sort this mess.
		 */
		struct v4l2_audio *vin = arg;
		ret = -EINVAL;
		if (vin->index > 0) break;
		strncpy(vin->name, "PVRUSB2 Audio",14);
		vin->capability = V4L2_AUDCAP_STEREO;
		ret = 0;
		break;
		break;
	}

	case VIDIOC_G_AUDIO:
	{
		/* pkt: FIXME: see above comment (VIDIOC_ENUMAUDIO) */
		struct v4l2_audio *vin = arg;
		memset(vin,0,sizeof(*vin));
		vin->index = 0;
		strncpy(vin->name, "PVRUSB2 Audio",14);
		vin->capability = V4L2_AUDCAP_STEREO;
		ret = 0;
		break;
	}

	case VIDIOC_G_TUNER:
	{
		struct v4l2_tuner *vt = (struct v4l2_tuner *)arg;

		if (vt->index != 0) break; /* Only answer for the 1st tuner */

		pvr2_hdw_execute_tuner_poll(hdw);
		ret = pvr2_hdw_get_tuner_status(hdw,vt);
		break;
	}

	case VIDIOC_S_TUNER:
	{
		struct v4l2_tuner *vt=(struct v4l2_tuner *)arg;

		if (vt->index != 0)
			break;

		ret = pvr2_ctrl_set_value(
			pvr2_hdw_get_ctrl_by_id(hdw,PVR2_CID_AUDIOMODE),
			vt->audmode);
		break;
	}

	case VIDIOC_S_FREQUENCY:
	{
		const struct v4l2_frequency *vf = (struct v4l2_frequency *)arg;
		unsigned long fv;
		struct v4l2_tuner vt;
		int cur_input;
		struct pvr2_ctrl *ctrlp;
		ret = pvr2_hdw_get_tuner_status(hdw,&vt);
		if (ret != 0) break;
		ctrlp = pvr2_hdw_get_ctrl_by_id(hdw,PVR2_CID_INPUT);
		ret = pvr2_ctrl_get_value(ctrlp,&cur_input);
		if (ret != 0) break;
		if (vf->type == V4L2_TUNER_RADIO) {
			if (cur_input != PVR2_CVAL_INPUT_RADIO) {
				pvr2_ctrl_set_value(ctrlp,
						    PVR2_CVAL_INPUT_RADIO);
			}
		} else {
			if (cur_input == PVR2_CVAL_INPUT_RADIO) {
				pvr2_ctrl_set_value(ctrlp,
						    PVR2_CVAL_INPUT_TV);
			}
		}
		fv = vf->frequency;
		if (vt.capability & V4L2_TUNER_CAP_LOW) {
			fv = (fv * 125) / 2;
		} else {
			fv = fv * 62500;
		}
		ret = pvr2_ctrl_set_value(
			pvr2_hdw_get_ctrl_by_id(hdw,PVR2_CID_FREQUENCY),fv);
		break;
	}

	case VIDIOC_G_FREQUENCY:
	{
		struct v4l2_frequency *vf = (struct v4l2_frequency *)arg;
		int val = 0;
		int cur_input;
		struct v4l2_tuner vt;
		ret = pvr2_hdw_get_tuner_status(hdw,&vt);
		if (ret != 0) break;
		ret = pvr2_ctrl_get_value(
			pvr2_hdw_get_ctrl_by_id(hdw,PVR2_CID_FREQUENCY),
			&val);
		if (ret != 0) break;
		pvr2_ctrl_get_value(
			pvr2_hdw_get_ctrl_by_id(hdw,PVR2_CID_INPUT),
			&cur_input);
		if (cur_input == PVR2_CVAL_INPUT_RADIO) {
			vf->type = V4L2_TUNER_RADIO;
		} else {
			vf->type = V4L2_TUNER_ANALOG_TV;
		}
		if (vt.capability & V4L2_TUNER_CAP_LOW) {
			val = (val * 2) / 125;
		} else {
			val /= 62500;
		}
		vf->frequency = val;
		break;
	}

	case VIDIOC_ENUM_FMT:
	{
		struct v4l2_fmtdesc *fd = (struct v4l2_fmtdesc *)arg;

		/* Only one format is supported : mpeg.*/
		if (fd->index != 0)
			break;

		memcpy(fd, pvr_fmtdesc, sizeof(struct v4l2_fmtdesc));
		ret = 0;
		break;
	}

	case VIDIOC_G_FMT:
	{
		struct v4l2_format *vf = (struct v4l2_format *)arg;
		int val;
		switch(vf->type) {
		case V4L2_BUF_TYPE_VIDEO_CAPTURE:
			memcpy(vf, &pvr_format[PVR_FORMAT_PIX],
			       sizeof(struct v4l2_format));
			val = 0;
			pvr2_ctrl_get_value(
				pvr2_hdw_get_ctrl_by_id(hdw,PVR2_CID_HRES),
				&val);
			vf->fmt.pix.width = val;
			val = 0;
			pvr2_ctrl_get_value(
				pvr2_hdw_get_ctrl_by_id(hdw,PVR2_CID_VRES),
				&val);
			vf->fmt.pix.height = val;
			ret = 0;
			break;
		case V4L2_BUF_TYPE_VBI_CAPTURE:
			// ????? Still need to figure out to do VBI correctly
			ret = -EINVAL;
			break;
		default:
			ret = -EINVAL;
			break;
		}
		break;
	}

	case VIDIOC_TRY_FMT:
	case VIDIOC_S_FMT:
	{
		struct v4l2_format *vf = (struct v4l2_format *)arg;

		ret = 0;
		switch(vf->type) {
		case V4L2_BUF_TYPE_VIDEO_CAPTURE: {
			int lmin,lmax,ldef;
			struct pvr2_ctrl *hcp,*vcp;
			int h = vf->fmt.pix.height;
			int w = vf->fmt.pix.width;
			hcp = pvr2_hdw_get_ctrl_by_id(hdw,PVR2_CID_HRES);
			vcp = pvr2_hdw_get_ctrl_by_id(hdw,PVR2_CID_VRES);

			lmin = pvr2_ctrl_get_min(hcp);
			lmax = pvr2_ctrl_get_max(hcp);
			pvr2_ctrl_get_def(hcp, &ldef);
			if (w == -1) {
				w = ldef;
			} else if (w < lmin) {
				w = lmin;
			} else if (w > lmax) {
				w = lmax;
			}
			lmin = pvr2_ctrl_get_min(vcp);
			lmax = pvr2_ctrl_get_max(vcp);
			pvr2_ctrl_get_def(vcp, &ldef);
			if (h == -1) {
				h = ldef;
			} else if (h < lmin) {
				h = lmin;
			} else if (h > lmax) {
				h = lmax;
			}

			memcpy(vf, &pvr_format[PVR_FORMAT_PIX],
			       sizeof(struct v4l2_format));
			vf->fmt.pix.width = w;
			vf->fmt.pix.height = h;

			if (cmd == VIDIOC_S_FMT) {
				pvr2_ctrl_set_value(hcp,vf->fmt.pix.width);
				pvr2_ctrl_set_value(vcp,vf->fmt.pix.height);
			}
		} break;
		case V4L2_BUF_TYPE_VBI_CAPTURE:
			// ????? Still need to figure out to do VBI correctly
			ret = -EINVAL;
			break;
		default:
			ret = -EINVAL;
			break;
		}
		break;
	}

	case VIDIOC_STREAMON:
	{
		if (!fh->pdi->stream) {
			/* No stream defined for this node.  This means
			   that we're not currently allowed to stream from
			   this node. */
			ret = -EPERM;
			break;
		}
		ret = pvr2_hdw_set_stream_type(hdw,pdi->config);
		if (ret < 0) return ret;
		ret = pvr2_hdw_set_streaming(hdw,!0);
		break;
	}

	case VIDIOC_STREAMOFF:
	{
		if (!fh->pdi->stream) {
			/* No stream defined for this node.  This means
			   that we're not currently allowed to stream from
			   this node. */
			ret = -EPERM;
			break;
		}
		ret = pvr2_hdw_set_streaming(hdw,0);
		break;
	}

	case VIDIOC_QUERYCTRL:
	{
		struct pvr2_ctrl *cptr;
		int val;
		struct v4l2_queryctrl *vc = (struct v4l2_queryctrl *)arg;
		ret = 0;
		if (vc->id & V4L2_CTRL_FLAG_NEXT_CTRL) {
			cptr = pvr2_hdw_get_ctrl_nextv4l(
				hdw,(vc->id & ~V4L2_CTRL_FLAG_NEXT_CTRL));
			if (cptr) vc->id = pvr2_ctrl_get_v4lid(cptr);
		} else {
			cptr = pvr2_hdw_get_ctrl_v4l(hdw,vc->id);
		}
		if (!cptr) {
			pvr2_trace(PVR2_TRACE_V4LIOCTL,
				   "QUERYCTRL id=0x%x not implemented here",
				   vc->id);
			ret = -EINVAL;
			break;
		}

		pvr2_trace(PVR2_TRACE_V4LIOCTL,
			   "QUERYCTRL id=0x%x mapping name=%s (%s)",
			   vc->id,pvr2_ctrl_get_name(cptr),
			   pvr2_ctrl_get_desc(cptr));
		strlcpy(vc->name,pvr2_ctrl_get_desc(cptr),sizeof(vc->name));
		vc->flags = pvr2_ctrl_get_v4lflags(cptr);
		pvr2_ctrl_get_def(cptr, &val);
		vc->default_value = val;
		switch (pvr2_ctrl_get_type(cptr)) {
		case pvr2_ctl_enum:
			vc->type = V4L2_CTRL_TYPE_MENU;
			vc->minimum = 0;
			vc->maximum = pvr2_ctrl_get_cnt(cptr) - 1;
			vc->step = 1;
			break;
		case pvr2_ctl_bool:
			vc->type = V4L2_CTRL_TYPE_BOOLEAN;
			vc->minimum = 0;
			vc->maximum = 1;
			vc->step = 1;
			break;
		case pvr2_ctl_int:
			vc->type = V4L2_CTRL_TYPE_INTEGER;
			vc->minimum = pvr2_ctrl_get_min(cptr);
			vc->maximum = pvr2_ctrl_get_max(cptr);
			vc->step = 1;
			break;
		default:
			pvr2_trace(PVR2_TRACE_V4LIOCTL,
				   "QUERYCTRL id=0x%x name=%s not mappable",
				   vc->id,pvr2_ctrl_get_name(cptr));
			ret = -EINVAL;
			break;
		}
		break;
	}

	case VIDIOC_QUERYMENU:
	{
		struct v4l2_querymenu *vm = (struct v4l2_querymenu *)arg;
		unsigned int cnt = 0;
		ret = pvr2_ctrl_get_valname(pvr2_hdw_get_ctrl_v4l(hdw,vm->id),
					    vm->index,
					    vm->name,sizeof(vm->name)-1,
					    &cnt);
		vm->name[cnt] = 0;
		break;
	}

	case VIDIOC_G_CTRL:
	{
		struct v4l2_control *vc = (struct v4l2_control *)arg;
		int val = 0;
		ret = pvr2_ctrl_get_value(pvr2_hdw_get_ctrl_v4l(hdw,vc->id),
					  &val);
		vc->value = val;
		break;
	}

	case VIDIOC_S_CTRL:
	{
		struct v4l2_control *vc = (struct v4l2_control *)arg;
		ret = pvr2_ctrl_set_value(pvr2_hdw_get_ctrl_v4l(hdw,vc->id),
					  vc->value);
		break;
	}

	case VIDIOC_G_EXT_CTRLS:
	{
		struct v4l2_ext_controls *ctls =
			(struct v4l2_ext_controls *)arg;
		struct v4l2_ext_control *ctrl;
		unsigned int idx;
		int val;
		ret = 0;
		for (idx = 0; idx < ctls->count; idx++) {
			ctrl = ctls->controls + idx;
			ret = pvr2_ctrl_get_value(
				pvr2_hdw_get_ctrl_v4l(hdw,ctrl->id),&val);
			if (ret) {
				ctls->error_idx = idx;
				break;
			}
			/* Ensure that if read as a 64 bit value, the user
			   will still get a hopefully sane value */
			ctrl->value64 = 0;
			ctrl->value = val;
		}
		break;
	}

	case VIDIOC_S_EXT_CTRLS:
	{
		struct v4l2_ext_controls *ctls =
			(struct v4l2_ext_controls *)arg;
		struct v4l2_ext_control *ctrl;
		unsigned int idx;
		ret = 0;
		for (idx = 0; idx < ctls->count; idx++) {
			ctrl = ctls->controls + idx;
			ret = pvr2_ctrl_set_value(
				pvr2_hdw_get_ctrl_v4l(hdw,ctrl->id),
				ctrl->value);
			if (ret) {
				ctls->error_idx = idx;
				break;
			}
		}
		break;
	}

	case VIDIOC_TRY_EXT_CTRLS:
	{
		struct v4l2_ext_controls *ctls =
			(struct v4l2_ext_controls *)arg;
		struct v4l2_ext_control *ctrl;
		struct pvr2_ctrl *pctl;
		unsigned int idx;
		/* For the moment just validate that the requested control
		   actually exists. */
		ret = 0;
		for (idx = 0; idx < ctls->count; idx++) {
			ctrl = ctls->controls + idx;
			pctl = pvr2_hdw_get_ctrl_v4l(hdw,ctrl->id);
			if (!pctl) {
				ret = -EINVAL;
				ctls->error_idx = idx;
				break;
			}
		}
		break;
	}

	case VIDIOC_CROPCAP:
	{
		struct v4l2_cropcap *cap = (struct v4l2_cropcap *)arg;
		if (cap->type != V4L2_BUF_TYPE_VIDEO_CAPTURE) {
			ret = -EINVAL;
			break;
		}
		ret = pvr2_hdw_get_cropcap(hdw, cap);
		cap->type = V4L2_BUF_TYPE_VIDEO_CAPTURE; /* paranoia */
		break;
	}
	case VIDIOC_G_CROP:
	{
		struct v4l2_crop *crop = (struct v4l2_crop *)arg;
		int val = 0;
		if (crop->type != V4L2_BUF_TYPE_VIDEO_CAPTURE) {
			ret = -EINVAL;
			break;
		}
		ret = pvr2_ctrl_get_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_CROPL), &val);
		if (ret != 0) {
			ret = -EINVAL;
			break;
		}
		crop->c.left = val;
		ret = pvr2_ctrl_get_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_CROPT), &val);
		if (ret != 0) {
			ret = -EINVAL;
			break;
		}
		crop->c.top = val;
		ret = pvr2_ctrl_get_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_CROPW), &val);
		if (ret != 0) {
			ret = -EINVAL;
			break;
		}
		crop->c.width = val;
		ret = pvr2_ctrl_get_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_CROPH), &val);
		if (ret != 0) {
			ret = -EINVAL;
			break;
		}
		crop->c.height = val;
	}
	case VIDIOC_S_CROP:
	{
		struct v4l2_crop *crop = (struct v4l2_crop *)arg;
		if (crop->type != V4L2_BUF_TYPE_VIDEO_CAPTURE) {
			ret = -EINVAL;
			break;
		}
		ret = pvr2_ctrl_set_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_CROPL),
			crop->c.left);
		if (ret != 0) {
			ret = -EINVAL;
			break;
		}
		ret = pvr2_ctrl_set_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_CROPT),
			crop->c.top);
		if (ret != 0) {
			ret = -EINVAL;
			break;
		}
		ret = pvr2_ctrl_set_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_CROPW),
			crop->c.width);
		if (ret != 0) {
			ret = -EINVAL;
			break;
		}
		ret = pvr2_ctrl_set_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_CROPH),
			crop->c.height);
		if (ret != 0) {
			ret = -EINVAL;
			break;
		}
	}
	case VIDIOC_LOG_STATUS:
	{
		pvr2_hdw_trigger_module_log(hdw);
		ret = 0;
		break;
	}
#ifdef CONFIG_VIDEO_ADV_DEBUG
	case VIDIOC_DBG_S_REGISTER:
	case VIDIOC_DBG_G_REGISTER:
	{
		u64 val;
		struct v4l2_dbg_register *req = (struct v4l2_dbg_register *)arg;
		if (cmd == VIDIOC_DBG_S_REGISTER) val = req->val;
		ret = pvr2_hdw_register_access(
			hdw, &req->match, req->reg,
			cmd == VIDIOC_DBG_S_REGISTER, &val);
		if (cmd == VIDIOC_DBG_G_REGISTER) req->val = val;
		break;
	}
#endif

	default :
		ret = -ENOTTY;
		break;
	}
