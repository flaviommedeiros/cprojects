if ((first_picture) ||
        (cur_dispbuf->bufWidth != vf->bufWidth) ||
        (cur_dispbuf->width != vf->width) ||
        (cur_dispbuf->height != vf->height) ||
#ifdef TV_3D_FUNCTION_OPEN
        ((process_3d_type&MODE_3D_AUTO)	&&
         (cur_dispbuf->trans_fmt != vf->trans_fmt))||
#endif
        (cur_dispbuf->ratio_control != vf->ratio_control) ||
        ((cur_dispbuf->type_backup & VIDTYPE_INTERLACE) !=
         (vf->type_backup & VIDTYPE_INTERLACE)) ||
         (cur_dispbuf->type != vf->type)
#if HAS_VPU_PROT
         || (cur_dispbuf->video_angle != vf->video_angle)
         || video_prot.angle_changed
#endif
         ) {
        amlog_mask(LOG_MASK_FRAMEINFO,
                   "%s %dx%d  ar=0x%x \n",
                   ((vf->type & VIDTYPE_TYPEMASK) == VIDTYPE_INTERLACE_TOP) ?
                   "interlace-top" :
                   ((vf->type & VIDTYPE_TYPEMASK) == VIDTYPE_INTERLACE_BOTTOM) ?
                   "interlace-bottom" :
                   "progressive",
                   vf->width,
                   vf->height,
                   vf->ratio_control);
#ifdef TV_3D_FUNCTION_OPEN
amlog_mask(LOG_MASK_FRAMEINFO,
                   "%s trans_fmt=%u \n",
                   __func__,
                   vf->trans_fmt);

#endif
        next_frame_par = (&frame_parms[0] == next_frame_par) ?
                         &frame_parms[1] : &frame_parms[0];
#if HAS_VPU_PROT
        if (use_prot) {
            vframe_t tmp_vf = *vf;
            video_prot.angle = vf->video_angle;
            if ((first_picture)||video_prot.angle_changed||(cur_dispbuf->video_angle != vf->video_angle || cur_dispbuf->width != vf->width || cur_dispbuf->height != vf->height)) {
                u32 angle_orientation = 0;
                video_prot_init(&video_prot, &tmp_vf);
                angle_orientation = vf->video_angle;
                video_prot_set_angle(&video_prot, angle_orientation);
                video_prot.angle = angle_orientation;
                video_prot.status = angle_orientation % 2;
                video_prot.angle_changed = 0;
                if(debug_flag& DEBUG_FLAG_BLACKOUT){
                  if(cur_dispbuf){
                  	printk("cur_dispbuf->width: %d  cur_dispbuf->height:%d -- vf->width:%d vf->height:%d\n", cur_dispbuf->width, cur_dispbuf->height,vf->width,vf->height);
                  }
                }
            }
            video_prot_revert_vframe(&video_prot, &tmp_vf);
            if (video_prot.status) {
                static vpp_frame_par_t prot_parms;
                prot_get_parameter(wide_setting, &tmp_vf, &prot_parms, vinfo);
                video_prot_axis(&video_prot, prot_parms.VPP_hd_start_lines_, prot_parms.VPP_hd_end_lines_, prot_parms.VPP_vd_start_lines_, prot_parms.VPP_vd_end_lines_);
				vpp_set_filters(process_3d_type,wide_setting, &tmp_vf, next_frame_par, vinfo);
                if (video_prot.status) {
                    u32 tmp_line_in_length_ = next_frame_par->VPP_hd_end_lines_ - next_frame_par->VPP_hd_start_lines_ + 1;
                    u32 tmp_pic_in_height_ = next_frame_par->VPP_vd_end_lines_ - next_frame_par->VPP_vd_start_lines_ + 1;
                    if (tmp_line_in_length_ < tmp_vf.width) {
                        next_frame_par->VPP_line_in_length_ = tmp_line_in_length_ / (next_frame_par->hscale_skip_count + 1);
                        next_frame_par->VPP_hd_start_lines_ = 0;
                        next_frame_par->VPP_hf_ini_phase_ = 0;
                        next_frame_par->VPP_hd_end_lines_ = tmp_line_in_length_ - 1;
                    }
                    if (tmp_pic_in_height_ < tmp_vf.height) {
                        next_frame_par->VPP_pic_in_height_ = tmp_pic_in_height_ / (next_frame_par->vscale_skip_count + 1);
                        next_frame_par->VPP_vd_start_lines_ = 0;
                        next_frame_par->VPP_hf_ini_phase_ = 0;
                        next_frame_par->VPP_vd_end_lines_ = tmp_pic_in_height_ - 1;
                    }
                }
            }else{
            	vpp_set_filters(process_3d_type,wide_setting, vf, next_frame_par, vinfo);
            }

        } else {
             video_prot.angle_changed = 0;
             vpp_set_filters(process_3d_type,wide_setting, vf, next_frame_par, vinfo);
        }
#else
         vpp_set_filters(process_3d_type,wide_setting, vf, next_frame_par, vinfo);
#endif
        /* apply new vpp settings */
        frame_par_ready_to_set = 1;

#if MESON_CPU_TYPE >= MESON_CPU_TYPE_MESON8
        if ((vf->width > 1920) && (vf->height > 1088)) {
            if (vpu_clk_level == 0) {
                vpu_clk_level = 1;

                spin_lock_irqsave(&lock, flags);
                vpu_delay_work_flag |= VPU_DELAYWORK_VPU_CLK;
                spin_unlock_irqrestore(&lock, flags);
            }
        } else {
            if (vpu_clk_level == 1) {
                vpu_clk_level = 0;

                spin_lock_irqsave(&lock, flags);
                vpu_delay_work_flag |= VPU_DELAYWORK_VPU_CLK;
                spin_unlock_irqrestore(&lock, flags);
            }
        }
#endif
    }
