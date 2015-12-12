#ifndef GE2D_NV
if(output_para.v4l2_format == V4L2_PIX_FMT_YUV420)
#else
		if(output_para.v4l2_format == V4L2_PIX_FMT_YVU420)
#endif
		{
			for(i=uv_height;i>0;i--) { /* copy y */
				memcpy((void *)(addr+poss),(void *)(buffer_u_start+posd),uv_width);
				poss+=uv_width;
				posd+= canvas_work_u.width;
			}
			posd=0;
			for(i=uv_height;i>0;i--) { /* copy y */
				memcpy((void *)(addr+poss),(void *)(buffer_v_start+posd),uv_width);
				poss+=uv_width;
				posd+= canvas_work_v.width;
			}
		}else{
			for(i=uv_height;i>0;i--) { /* copy v */
				memcpy((void *)(addr+poss),(void *)(buffer_v_start+posd),uv_width);
				poss+=uv_width;
				posd+= canvas_work_v.width;
			}
			posd=0;
			for(i=uv_height;i>0;i--) { /* copy u */
				memcpy((void *)(addr+poss),(void *)(buffer_u_start+posd),uv_width);
				poss+=uv_width;
				posd+= canvas_work_u.width;
			}
		}
