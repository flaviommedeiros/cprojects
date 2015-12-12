if (in_buf_num>bypass_get_buf_threshold
#ifdef DET3D
			&& (di_pre_stru.vframe_interleave_flag == 0)
#endif
			) {
			return 0;
		}
