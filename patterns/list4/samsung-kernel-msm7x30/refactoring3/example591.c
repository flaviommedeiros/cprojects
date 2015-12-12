switch (cmd) {
	case VIDIOC_QUERYCTRL:
		return v4l2_queryctrl(vfh->ctrl_handler, arg);

	case VIDIOC_QUERYMENU:
		return v4l2_querymenu(vfh->ctrl_handler, arg);

	case VIDIOC_G_CTRL:
		return v4l2_g_ctrl(vfh->ctrl_handler, arg);

	case VIDIOC_S_CTRL:
		return v4l2_s_ctrl(vfh, vfh->ctrl_handler, arg);

	case VIDIOC_G_EXT_CTRLS:
		return v4l2_g_ext_ctrls(vfh->ctrl_handler, arg);

	case VIDIOC_S_EXT_CTRLS:
		return v4l2_s_ext_ctrls(vfh, vfh->ctrl_handler, arg);

	case VIDIOC_TRY_EXT_CTRLS:
		return v4l2_try_ext_ctrls(vfh->ctrl_handler, arg);

	case VIDIOC_DQEVENT:
		if (!(sd->flags & V4L2_SUBDEV_FL_HAS_EVENTS))
			return -ENOIOCTLCMD;

		return v4l2_event_dequeue(vfh, arg, file->f_flags & O_NONBLOCK);

	case VIDIOC_SUBSCRIBE_EVENT:
		return v4l2_subdev_call(sd, core, subscribe_event, vfh, arg);

	case VIDIOC_UNSUBSCRIBE_EVENT:
		return v4l2_subdev_call(sd, core, unsubscribe_event, vfh, arg);

#ifdef CONFIG_VIDEO_ADV_DEBUG
	case VIDIOC_DBG_G_REGISTER:
	{
		struct v4l2_dbg_register *p = arg;

		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		return v4l2_subdev_call(sd, core, g_register, p);
	}
	case VIDIOC_DBG_S_REGISTER:
	{
		struct v4l2_dbg_register *p = arg;

		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		return v4l2_subdev_call(sd, core, s_register, p);
	}
#endif

	case VIDIOC_LOG_STATUS: {
		int ret;

		pr_info("%s: =================  START STATUS  =================\n",
			sd->name);
		ret = v4l2_subdev_call(sd, core, log_status);
		pr_info("%s: ==================  END STATUS  ==================\n",
			sd->name);
		return ret;
	}

#if defined(CONFIG_VIDEO_V4L2_SUBDEV_API)
	case VIDIOC_SUBDEV_G_FMT: {
		struct v4l2_subdev_format *format = arg;

		if (format->which != V4L2_SUBDEV_FORMAT_TRY &&
		    format->which != V4L2_SUBDEV_FORMAT_ACTIVE)
			return -EINVAL;

		if (format->pad >= sd->entity.num_pads)
			return -EINVAL;

		return v4l2_subdev_call(sd, pad, get_fmt, subdev_fh, format);
	}

	case VIDIOC_SUBDEV_S_FMT: {
		struct v4l2_subdev_format *format = arg;

		if (format->which != V4L2_SUBDEV_FORMAT_TRY &&
		    format->which != V4L2_SUBDEV_FORMAT_ACTIVE)
			return -EINVAL;

		if (format->pad >= sd->entity.num_pads)
			return -EINVAL;

		return v4l2_subdev_call(sd, pad, set_fmt, subdev_fh, format);
	}

	case VIDIOC_SUBDEV_G_CROP: {
		struct v4l2_subdev_crop *crop = arg;

		if (crop->which != V4L2_SUBDEV_FORMAT_TRY &&
		    crop->which != V4L2_SUBDEV_FORMAT_ACTIVE)
			return -EINVAL;

		if (crop->pad >= sd->entity.num_pads)
			return -EINVAL;

		return v4l2_subdev_call(sd, pad, get_crop, subdev_fh, crop);
	}

	case VIDIOC_SUBDEV_S_CROP: {
		struct v4l2_subdev_crop *crop = arg;

		if (crop->which != V4L2_SUBDEV_FORMAT_TRY &&
		    crop->which != V4L2_SUBDEV_FORMAT_ACTIVE)
			return -EINVAL;

		if (crop->pad >= sd->entity.num_pads)
			return -EINVAL;

		return v4l2_subdev_call(sd, pad, set_crop, subdev_fh, crop);
	}

	case VIDIOC_SUBDEV_ENUM_MBUS_CODE: {
		struct v4l2_subdev_mbus_code_enum *code = arg;

		if (code->pad >= sd->entity.num_pads)
			return -EINVAL;

		return v4l2_subdev_call(sd, pad, enum_mbus_code, subdev_fh,
					code);
	}

	case VIDIOC_SUBDEV_ENUM_FRAME_SIZE: {
		struct v4l2_subdev_frame_size_enum *fse = arg;

		if (fse->pad >= sd->entity.num_pads)
			return -EINVAL;

		return v4l2_subdev_call(sd, pad, enum_frame_size, subdev_fh,
					fse);
	}

	case VIDIOC_SUBDEV_G_FRAME_INTERVAL:
		return v4l2_subdev_call(sd, video, g_frame_interval, arg);

	case VIDIOC_SUBDEV_S_FRAME_INTERVAL:
		return v4l2_subdev_call(sd, video, s_frame_interval, arg);

	case VIDIOC_SUBDEV_ENUM_FRAME_INTERVAL: {
		struct v4l2_subdev_frame_interval_enum *fie = arg;

		if (fie->pad >= sd->entity.num_pads)
			return -EINVAL;

		return v4l2_subdev_call(sd, pad, enum_frame_interval, subdev_fh,
					fie);
	}
#endif
	default:
		return v4l2_subdev_call(sd, core, ioctl, cmd, arg);
	}
