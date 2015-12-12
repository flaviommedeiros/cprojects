switch (qc->id) {
#ifdef PRIVATE_CIDS
	case V4L2_CID_MOTION_TRACE:
		qc->type = V4L2_CTRL_TYPE_BOOLEAN;
		qc->minimum = 0;
		qc->maximum = qc->step = 1;
		qc->default_value = 0;
		strlcpy(qc->name, "Motion Detection Trace", sizeof(qc->name));
		return 0;
#else
	case V4L2_CID_MOTION_TRACE:
		return v4l2_ctrl_query_fill(qc, 0, 1, 1, 0);
#endif
	}
