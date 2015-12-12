#ifdef CONFIG_POST_PROCESS_MANAGER_PPSCALER
if (video_scaler_mode) {
                axis[0] = content_left;
                axis[1] = content_top;
                axis[2] = content_w;
                axis[3] = content_h;
            } else
#endif
            {
                vpp_get_video_layer_position(&axis[0], &axis[1], &axis[2], &axis[3]);
            }
