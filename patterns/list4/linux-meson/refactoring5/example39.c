#ifdef FORCE_BOB_SUPPORT
if (force_bob_flag != 0) {
						force_bob_vframe(di_buf);
						frame_count++;
					}
					else
#endif
					{
						di_buf->vframe->type = VIDTYPE_PROGRESSIVE| VIDTYPE_VIU_422 | VIDTYPE_VIU_SINGLE_PLANE | VIDTYPE_VIU_FIELD;
						if (di_buf->di_buf_dup_p[1]->new_format_flag) { //if (di_buf->di_buf_dup_p[1]->post_proc_flag == 2) {
							di_buf->vframe->early_process_fun = de_post_disable_fun;
						}
						else{
							di_buf->vframe->early_process_fun = do_nothing_fun;
						}

						if (di_buf->di_buf_dup_p[1]->type == VFRAME_TYPE_IN) { /* next will be bypass */
							di_buf->vframe->type = VIDTYPE_PROGRESSIVE | VIDTYPE_VIU_422 | VIDTYPE_VIU_SINGLE_PLANE | VIDTYPE_VIU_FIELD;
							di_buf->vframe->height >>= 1;
							di_buf->vframe->canvas0Addr = di_buf->di_buf_dup_p[0]->nr_canvas_idx; //top
							di_buf->vframe->canvas1Addr = di_buf->di_buf_dup_p[0]->nr_canvas_idx;
							di_buf->vframe->process_fun = NULL;
							di_buf->process_fun_index = PROCESS_FUN_NULL;
						}
						else {

						/*for debug*/
							if (debug_blend_mode != -1)
								di_buf->pulldown_mode = debug_blend_mode;
							di_buf->vframe->process_fun = de_post_process;
							di_buf->process_fun_index = PROCESS_FUN_DI;
							inc_post_ref_count(di_buf);
						}
						di_buf->di_buf[0] = di_buf->di_buf_dup_p[0];
						di_buf->di_buf[1] = NULL;
						queue_out(di_buf->di_buf[0]);
			if (frame_count == 0) {
							di_post_stru.start_pts = di_buf->vframe->pts;
						}
						di_lock_irqfiq_save(irq_flag2, fiq_flag);
						if ((frame_count<start_frame_drop_count) ||
							(di_buf->di_buf_dup_p[0]->throw_flag) || (di_buf->di_buf_dup_p[1]->throw_flag) || (di_buf->di_buf_dup_p[2]->throw_flag)) {
							queue_in(di_buf, QUEUE_TMP);
							recycle_vframe_type_post(di_buf);
#ifdef DI_DEBUG
							recycle_vframe_type_post_print(di_buf, __func__, __LINE__);
#endif
						}
						else{
				if (frame_count == start_frame_drop_count) {
								if ((di_post_stru.start_pts != 0) && (di_buf->vframe->pts == 0))
									di_buf->vframe->pts = di_post_stru.start_pts;
								di_post_stru.start_pts = 0;
							}
							queue_in(di_buf, QUEUE_POST_READY);
						}
						frame_count++;
						di_unlock_irqfiq_restore(irq_flag2, fiq_flag);
					}
