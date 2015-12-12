#ifdef TV_3D_FUNCTION_OPEN
if((cur_frame_par->hscale_skip_count)&&(cur_dispbuf->type & VIDTYPE_VIU_FIELD)){
        	VSYNC_WR_MPEG_REG_BITS(VIU_VD1_FMT_CTRL + cur_dev->viu_off,0,20,1);//HFORMATTER_EN
		VSYNC_WR_MPEG_REG_BITS(VIU_VD2_FMT_CTRL + cur_dev->viu_off,0,20,1);//HFORMATTER_EN
	}
