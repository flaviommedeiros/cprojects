#ifdef TV_3D_FUNCTION_OPEN
if (next_frame_par->vpp_3d_mode == VPP_3D_MODE_LA)
		next_frame_par->vscale_skip_count += 2;
		else
#endif
				next_frame_par->vscale_skip_count++;
