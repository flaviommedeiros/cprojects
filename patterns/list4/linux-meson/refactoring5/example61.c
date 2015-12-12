#ifdef TV_REVERSE
if (reverse)
	{
		/* calculate source vertical clip */
		if (video_top < 0) {
			if (start < 0) {
				temp = (-start * ratio_y) >> 18;
			next_frame_par->VPP_vd_end_lines_ = h_in - 1 - temp;

		} else {
			next_frame_par->VPP_vd_end_lines_ = h_in - 1;
		}

	} else {
		if (start < video_top) {
			temp = ((video_top - start) * ratio_y) >> 18;
			next_frame_par->VPP_vd_end_lines_ = h_in - 1 - temp;
			} else {
				next_frame_par->VPP_vd_end_lines_ = h_in - 1;
			}
		}
		temp = next_frame_par->VPP_vd_end_lines_ - (video_height * ratio_y >> 18);
		next_frame_par->VPP_vd_start_lines_ = (temp >= 0) ? temp : 0;
	}
	else
#endif
	{
	if (video_top < 0) {
		if (start < 0) {
			temp = (-start * ratio_y) >> 18;
			next_frame_par->VPP_vd_start_lines_ = temp;

		} else {
			next_frame_par->VPP_vd_start_lines_ = 0;
		}

	} else {
		if (start < video_top) {
			temp = ((video_top - start) * ratio_y) >> 18;
			next_frame_par->VPP_vd_start_lines_ = temp;

		} else {
			next_frame_par->VPP_vd_start_lines_ = 0;
		}
	}

	temp = next_frame_par->VPP_vd_start_lines_ + (video_height * ratio_y >> 18);
	next_frame_par->VPP_vd_end_lines_ = (temp <= (h_in - 1)) ? temp : (h_in - 1);
	}
