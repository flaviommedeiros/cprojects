#ifdef TV_REVERSE
if (reverse)
	{
	if (video_left < 0) {
		if (start < 0) {
			temp = (-start * ratio_x) >> 18;
			next_frame_par->VPP_hd_end_lines_ = w_in - 1 - temp;
		} else {
			next_frame_par->VPP_hd_end_lines_ = w_in - 1;
		}
	} else {
		if (start < video_left) {
			temp = ((video_left - start) * ratio_x) >> 18;
			next_frame_par->VPP_hd_end_lines_ = w_in - 1 - temp;
		} else {
			next_frame_par->VPP_hd_end_lines_ = w_in - 1;
		}
	}
	temp = next_frame_par->VPP_hd_end_lines_ - (video_width * ratio_x >> 18);
	next_frame_par->VPP_hd_start_lines_ = (temp >= 0) ? temp : 0;
	}
	else
#endif
	{
		if (video_left < 0) {
			if (start < 0) {
				temp = (-start * ratio_x) >> 18;
				next_frame_par->VPP_hd_start_lines_ = temp;

			} else {
				next_frame_par->VPP_hd_start_lines_ = 0;
			}

		} else {
			if (start < video_left) {
				temp = ((video_left - start) * ratio_x) >> 18;
				next_frame_par->VPP_hd_start_lines_ = temp;

			} else {
				next_frame_par->VPP_hd_start_lines_ = 0;
			}
		}

		temp = next_frame_par->VPP_hd_start_lines_ + (video_width * ratio_x >> 18);
		next_frame_par->VPP_hd_end_lines_ = (temp <= (w_in - 1)) ? temp : (w_in - 1);
	}
