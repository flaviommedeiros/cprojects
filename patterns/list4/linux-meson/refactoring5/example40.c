#ifdef SUPPORT_START_FRAME_HOLD
if ((disp_frame_count == 0) && (is_bypass(NULL) == 0)) {
		int ready_count = list_count(QUEUE_POST_READY);
		if (ready_count>start_frame_hold_count) {
		   di_buf = get_di_buf_head(QUEUE_POST_READY);
		   if (di_buf) {
		   vframe_ret = di_buf->vframe;
		}
	}
	}
	else
#endif
	{
	if (!queue_empty(QUEUE_POST_READY)) {
	   di_buf = get_di_buf_head(QUEUE_POST_READY);
	   if (di_buf) {
	   vframe_ret = di_buf->vframe;
	}
	}
	}
