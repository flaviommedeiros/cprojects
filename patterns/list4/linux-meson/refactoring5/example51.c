#ifdef CONFIG_POST_PROCESS_MANAGER_PPSCALER
if(video_scaler_mode){
            if ((w == 1) && (h == 1)){
                w= 0;
                h = 0;
            }
            if((content_left!=parsed[0])||(content_top!=parsed[1])||(content_w!=w)||(content_h!=h))
                scaler_pos_changed = 1;
            content_left = parsed[0];
            content_top = parsed[1];
            content_w = w;
            content_h = h;   
            //video_notify_flag = video_notify_flag|VIDEO_NOTIFY_POS_CHANGED;
        }else
#endif
        {
            if ((w == 1) && (h == 1)) {
                w = h = 0;
                vpp2_set_video_layer_position(parsed[0], parsed[1], 0, 0);
            } else if ((w > 0) && (h > 0)) {
                vpp2_set_video_layer_position(parsed[0], parsed[1], w, h);
            }
        }
