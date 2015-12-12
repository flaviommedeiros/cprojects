#ifndef USE_AVS_SEQ_INFO
if(vavs_amstream_dec_info.rate > 0){
        *duration = vavs_amstream_dec_info.rate;
    }
    else
#endif
    {
        *duration = frame_rate_tab[READ_VREG(AVS_FRAME_RATE)&0xf];
        //printk("%s: duration = %d\n", __func__, *duration);
        frame_dur = *duration;
    }
