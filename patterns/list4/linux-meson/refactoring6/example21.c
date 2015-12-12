if(output_para.v4l2_format==V4L2_PIX_FMT_YUV420||
		output_para.v4l2_format==V4L2_PIX_FMT_YVU420
#ifndef GE2D_NV
		||output_para.v4l2_format==V4L2_PIX_FMT_NV12||
		output_para.v4l2_format==V4L2_PIX_FMT_NV21
#endif
			) {
		canvas_read((output_para.index>>16)&0xff,&cd);
		ge2d_config->dst_planes[0].addr = cd.addr;
		ge2d_config->dst_planes[0].w = cd.width;
		ge2d_config->dst_planes[0].h = cd.height;
		ge2d_config->dst_para.canvas_index=(output_para.index>>16)&0xff;
#ifndef GE2D_NV
		ge2d_config->dst_para.format=GE2D_FORMAT_S8_CR|GE2D_LITTLE_ENDIAN;
#else
		ge2d_config->dst_para.format=GE2D_FORMAT_S8_CB|GE2D_LITTLE_ENDIAN;
#endif
		ge2d_config->dst_para.width = output_para.width/2;
		ge2d_config->dst_para.height = output_para.height/2;
		ge2d_config->dst_xy_swap = 0;

		if(current_mirror==1){
			ge2d_config->dst_para.x_rev = 1;
			ge2d_config->dst_para.y_rev = 0;
		}else if(current_mirror==2){
			ge2d_config->dst_para.x_rev = 0;
			ge2d_config->dst_para.y_rev = 1;
		}else{
			ge2d_config->dst_para.x_rev = 0;
			ge2d_config->dst_para.y_rev = 0;
		}

		if(cur_angle==90){
			ge2d_config->dst_xy_swap = 1;
			ge2d_config->dst_para.x_rev ^= 1;
		}else if(cur_angle==180){
			ge2d_config->dst_para.x_rev ^= 1;
			ge2d_config->dst_para.y_rev ^= 1;
		}else if(cur_angle==270){
			ge2d_config->dst_xy_swap = 1;
			ge2d_config->dst_para.y_rev ^= 1;
		}

		if(ge2d_context_config_ex(context,ge2d_config)<0) {
			printk("++ge2d configing error.\n");
			return -1;
		}
		stretchblt_noalpha(context, src_left, src_top, src_width, src_height,
			0, 0, ge2d_config->dst_para.width, ge2d_config->dst_para.height);
	}
