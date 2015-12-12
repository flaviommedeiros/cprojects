switch (qc->id) {
	case V4L2_CID_BRIGHTNESS:
	case V4L2_CID_CONTRAST:
	case V4L2_CID_SATURATION:
	case V4L2_CID_HUE:
		return v4l2_ctrl_query_fill(qc, 0x00, 0xff, 1, 0x80);
	case V4L2_CID_SHARPNESS:
		return v4l2_ctrl_query_fill(qc, 0x00, 0x0f, 1, 0x00);
	case V4L2_CID_MPEG_VIDEO_ENCODING:
		return v4l2_ctrl_query_fill(
			qc, V4L2_MPEG_VIDEO_ENCODING_MPEG_1,
			V4L2_MPEG_VIDEO_ENCODING_MPEG_4_AVC, 1,
			V4L2_MPEG_VIDEO_ENCODING_MPEG_4_AVC);
	case V4L2_CID_MPEG_VIDEO_GOP_SIZE:
		return v4l2_ctrl_query_fill(qc, 1, 255, 1, solo_dev->fps);
#ifdef PRIVATE_CIDS
	case V4L2_CID_MOTION_THRESHOLD:
		qc->flags |= V4L2_CTRL_FLAG_SLIDER;
		qc->type = V4L2_CTRL_TYPE_INTEGER;
		qc->minimum = 0;
		qc->maximum = 0xffff;
		qc->step = 1;
		qc->default_value = SOLO_DEF_MOT_THRESH;
		strlcpy(qc->name, "Motion Detection Threshold",
			sizeof(qc->name));
		return 0;
	case V4L2_CID_MOTION_ENABLE:
		qc->type = V4L2_CTRL_TYPE_BOOLEAN;
		qc->minimum = 0;
		qc->maximum = qc->step = 1;
		qc->default_value = 0;
		strlcpy(qc->name, "Motion Detection Enable", sizeof(qc->name));
		return 0;
#else
	case V4L2_CID_MOTION_THRESHOLD:
		return v4l2_ctrl_query_fill(qc, 0, 0xffff, 1,
					    SOLO_DEF_MOT_THRESH);
	case V4L2_CID_MOTION_ENABLE:
		return v4l2_ctrl_query_fill(qc, 0, 1, 1, 0);
#endif
	case V4L2_CID_RDS_TX_RADIO_TEXT:
		qc->type = V4L2_CTRL_TYPE_STRING;
		qc->minimum = 0;
		qc->maximum = OSD_TEXT_MAX;
		qc->step = 1;
		qc->default_value = 0;
		strlcpy(qc->name, "OSD Text", sizeof(qc->name));
		return 0;
	}
