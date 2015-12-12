#ifndef USE_AVS_SEQ_INFO
if(vavs_amstream_dec_info.width>0 && vavs_amstream_dec_info.height>0){
        vf->width = vavs_amstream_dec_info.width;
        vf->height = vavs_amstream_dec_info.height;
    }
    else
#endif
    {
        vf->width  = READ_VREG(AVS_PIC_WIDTH);
        vf->height = READ_VREG(AVS_PIC_HEIGHT);
        frame_width = vf->width;
        frame_height = vf->height;
        //printk("%s: (%d,%d)\n", __func__,vf->width, vf->height);
    }
