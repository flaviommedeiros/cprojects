#ifdef SUPPORT_START_FRAME_HOLD
if ((disp_frame_count == 0) && (is_bypass(NULL) == 0)) {
		int ready_count = list_count(QUEUE_POST_READY);
		if (ready_count>start_frame_hold_count) {
			goto get_vframe;
		}
	}
	else
#endif
	if (!queue_empty(QUEUE_POST_READY)) {
#ifdef SUPPORT_START_FRAME_HOLD
get_vframe:
#endif
		log_buffer_state("ge_");
		di_lock_irqfiq_save(irq_flag2, fiq_flag);

	   di_buf = get_di_buf_head(QUEUE_POST_READY);
	   queue_out(di_buf);
	   queue_in(di_buf, QUEUE_DISPLAY); //add it into display_list

		di_unlock_irqfiq_restore(irq_flag2, fiq_flag);

	   if (di_buf) {
	   vframe_ret = di_buf->vframe;
		}
	   disp_frame_count++;
	   if (run_flag == DI_RUN_FLAG_STEP) {
			run_flag = DI_RUN_FLAG_STEP_DONE;
	   }
	   log_buffer_state("get");
	}
