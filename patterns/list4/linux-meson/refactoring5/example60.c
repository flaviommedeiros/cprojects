#ifdef SUPER_SCALER_OPEN
if (next_frame_par->supscl_path) {
			video_top = (video_layer_top>>next_frame_par->supsc1_vert_ratio);
			video_height = (video_layer_height>>next_frame_par->supsc1_vert_ratio);
			video_left = (video_layer_left>>next_frame_par->supsc1_hori_ratio);
			video_width = (video_layer_width>>next_frame_par->supsc1_hori_ratio);
		}else
		#endif
		{
			video_top = video_layer_top;
			video_left = video_layer_left;
			video_width = video_layer_width;
			video_height = video_layer_height;
		}
