#ifdef CONFIG_POST_PROCESS_MANAGER_PPSCALER
if(video_scaler_mode){
        x = content_left;
        y = content_top;
        w = content_w;
        h = content_h;
    }else
#endif
    {
        vpp_get_video_layer_position(&x, &y, &w, &h);
    }
