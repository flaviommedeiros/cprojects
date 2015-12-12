static void __sdma_process_event(struct sdma_engine *sde,
	enum sdma_events event)
{
	struct sdma_state *ss = &sde->state;
	int need_progress = 0;

	/* CONFIG SDMA temporary */
#ifdef CONFIG_SDMA_VERBOSITY
	dd_dev_err(sde->dd, "CONFIG SDMA(%u) [%s] %s\n", sde->this_idx,
		   sdma_state_names[ss->current_state],
		   sdma_event_names[event]);
#endif

	switch (ss->current_state) {
	case sdma_state_s00_hw_down:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			break;
		case sdma_event_e30_go_running:
			/*
			 * If down, but running requested (usually result
			 * of link up, then we need to start up.
			 * This can happen when hw down is requested while
			 * bringing the link up with traffic active on
			 * 7220, e.g. */
			ss->go_s99_running = 1;
			/* fall through and start dma engine */
		case sdma_event_e10_go_hw_start:
			/* This reference means the state machine is started */
			sdma_get(&sde->state);
			sdma_set_state(sde,
				sdma_state_s10_hw_start_up_halt_wait);
			break;
		case sdma_event_e15_hw_halt_done:
			break;
		case sdma_event_e25_hw_clean_up_done:
			break;
		case sdma_event_e40_sw_cleaned:
			sdma_sw_tear_down(sde);
			break;
		case sdma_event_e50_hw_cleaned:
			break;
		case sdma_event_e60_hw_halted:
			break;
		case sdma_event_e70_go_idle:
			break;
		case sdma_event_e80_hw_freeze:
			break;
		case sdma_event_e81_hw_frozen:
			break;
		case sdma_event_e82_hw_unfreeze:
			break;
		case sdma_event_e85_link_down:
			break;
		case sdma_event_e90_sw_halted:
			break;
		}
		break;

	case sdma_state_s10_hw_start_up_halt_wait:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			sdma_set_state(sde, sdma_state_s00_hw_down);
			sdma_sw_tear_down(sde);
			break;
		case sdma_event_e10_go_hw_start:
			break;
		case sdma_event_e15_hw_halt_done:
			sdma_set_state(sde,
				sdma_state_s15_hw_start_up_clean_wait);
			sdma_start_hw_clean_up(sde);
			break;
		case sdma_event_e25_hw_clean_up_done:
			break;
		case sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			break;
		case sdma_event_e40_sw_cleaned:
			break;
		case sdma_event_e50_hw_cleaned:
			break;
		case sdma_event_e60_hw_halted:
			sdma_start_err_halt_wait(sde);
			break;
		case sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			break;
		case sdma_event_e80_hw_freeze:
			break;
		case sdma_event_e81_hw_frozen:
			break;
		case sdma_event_e82_hw_unfreeze:
			break;
		case sdma_event_e85_link_down:
			break;
		case sdma_event_e90_sw_halted:
			break;
		}
		break;

	case sdma_state_s15_hw_start_up_clean_wait:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			sdma_set_state(sde, sdma_state_s00_hw_down);
			sdma_sw_tear_down(sde);
			break;
		case sdma_event_e10_go_hw_start:
			break;
		case sdma_event_e15_hw_halt_done:
			break;
		case sdma_event_e25_hw_clean_up_done:
			sdma_hw_start_up(sde);
			sdma_set_state(sde, ss->go_s99_running ?
				       sdma_state_s99_running :
				       sdma_state_s20_idle);
			break;
		case sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			break;
		case sdma_event_e40_sw_cleaned:
			break;
		case sdma_event_e50_hw_cleaned:
			break;
		case sdma_event_e60_hw_halted:
			break;
		case sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			break;
		case sdma_event_e80_hw_freeze:
			break;
		case sdma_event_e81_hw_frozen:
			break;
		case sdma_event_e82_hw_unfreeze:
			break;
		case sdma_event_e85_link_down:
			break;
		case sdma_event_e90_sw_halted:
			break;
		}
		break;

	case sdma_state_s20_idle:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			sdma_set_state(sde, sdma_state_s00_hw_down);
			sdma_sw_tear_down(sde);
			break;
		case sdma_event_e10_go_hw_start:
			break;
		case sdma_event_e15_hw_halt_done:
			break;
		case sdma_event_e25_hw_clean_up_done:
			break;
		case sdma_event_e30_go_running:
			sdma_set_state(sde, sdma_state_s99_running);
			ss->go_s99_running = 1;
			break;
		case sdma_event_e40_sw_cleaned:
			break;
		case sdma_event_e50_hw_cleaned:
			break;
		case sdma_event_e60_hw_halted:
			sdma_set_state(sde, sdma_state_s50_hw_halt_wait);
			sdma_start_err_halt_wait(sde);
			break;
		case sdma_event_e70_go_idle:
			break;
		case sdma_event_e85_link_down:
			/* fall through */
		case sdma_event_e80_hw_freeze:
			sdma_set_state(sde, sdma_state_s80_hw_freeze);
			atomic_dec(&sde->dd->sdma_unfreeze_count);
			wake_up_interruptible(&sde->dd->sdma_unfreeze_wq);
			break;
		case sdma_event_e81_hw_frozen:
			break;
		case sdma_event_e82_hw_unfreeze:
			break;
		case sdma_event_e90_sw_halted:
			break;
		}
		break;

	case sdma_state_s30_sw_clean_up_wait:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			sdma_set_state(sde, sdma_state_s00_hw_down);
			break;
		case sdma_event_e10_go_hw_start:
			break;
		case sdma_event_e15_hw_halt_done:
			break;
		case sdma_event_e25_hw_clean_up_done:
			break;
		case sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			break;
		case sdma_event_e40_sw_cleaned:
			sdma_set_state(sde, sdma_state_s40_hw_clean_up_wait);
			sdma_start_hw_clean_up(sde);
			break;
		case sdma_event_e50_hw_cleaned:
			break;
		case sdma_event_e60_hw_halted:
			break;
		case sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			break;
		case sdma_event_e80_hw_freeze:
			break;
		case sdma_event_e81_hw_frozen:
			break;
		case sdma_event_e82_hw_unfreeze:
			break;
		case sdma_event_e85_link_down:
			ss->go_s99_running = 0;
			break;
		case sdma_event_e90_sw_halted:
			break;
		}
		break;

	case sdma_state_s40_hw_clean_up_wait:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			sdma_set_state(sde, sdma_state_s00_hw_down);
			sdma_start_sw_clean_up(sde);
			break;
		case sdma_event_e10_go_hw_start:
			break;
		case sdma_event_e15_hw_halt_done:
			break;
		case sdma_event_e25_hw_clean_up_done:
			sdma_hw_start_up(sde);
			sdma_set_state(sde, ss->go_s99_running ?
				       sdma_state_s99_running :
				       sdma_state_s20_idle);
			break;
		case sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			break;
		case sdma_event_e40_sw_cleaned:
			break;
		case sdma_event_e50_hw_cleaned:
			break;
		case sdma_event_e60_hw_halted:
			break;
		case sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			break;
		case sdma_event_e80_hw_freeze:
			break;
		case sdma_event_e81_hw_frozen:
			break;
		case sdma_event_e82_hw_unfreeze:
			break;
		case sdma_event_e85_link_down:
			ss->go_s99_running = 0;
			break;
		case sdma_event_e90_sw_halted:
			break;
		}
		break;

	case sdma_state_s50_hw_halt_wait:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			sdma_set_state(sde, sdma_state_s00_hw_down);
			sdma_start_sw_clean_up(sde);
			break;
		case sdma_event_e10_go_hw_start:
			break;
		case sdma_event_e15_hw_halt_done:
			sdma_set_state(sde, sdma_state_s30_sw_clean_up_wait);
			sdma_start_sw_clean_up(sde);
			break;
		case sdma_event_e25_hw_clean_up_done:
			break;
		case sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			break;
		case sdma_event_e40_sw_cleaned:
			break;
		case sdma_event_e50_hw_cleaned:
			break;
		case sdma_event_e60_hw_halted:
			sdma_start_err_halt_wait(sde);
			break;
		case sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			break;
		case sdma_event_e80_hw_freeze:
			break;
		case sdma_event_e81_hw_frozen:
			break;
		case sdma_event_e82_hw_unfreeze:
			break;
		case sdma_event_e85_link_down:
			ss->go_s99_running = 0;
			break;
		case sdma_event_e90_sw_halted:
			break;
		}
		break;

	case sdma_state_s60_idle_halt_wait:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			sdma_set_state(sde, sdma_state_s00_hw_down);
			sdma_start_sw_clean_up(sde);
			break;
		case sdma_event_e10_go_hw_start:
			break;
		case sdma_event_e15_hw_halt_done:
			sdma_set_state(sde, sdma_state_s30_sw_clean_up_wait);
			sdma_start_sw_clean_up(sde);
			break;
		case sdma_event_e25_hw_clean_up_done:
			break;
		case sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			break;
		case sdma_event_e40_sw_cleaned:
			break;
		case sdma_event_e50_hw_cleaned:
			break;
		case sdma_event_e60_hw_halted:
			sdma_start_err_halt_wait(sde);
			break;
		case sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			break;
		case sdma_event_e80_hw_freeze:
			break;
		case sdma_event_e81_hw_frozen:
			break;
		case sdma_event_e82_hw_unfreeze:
			break;
		case sdma_event_e85_link_down:
			break;
		case sdma_event_e90_sw_halted:
			break;
		}
		break;

	case sdma_state_s80_hw_freeze:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			sdma_set_state(sde, sdma_state_s00_hw_down);
			sdma_start_sw_clean_up(sde);
			break;
		case sdma_event_e10_go_hw_start:
			break;
		case sdma_event_e15_hw_halt_done:
			break;
		case sdma_event_e25_hw_clean_up_done:
			break;
		case sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			break;
		case sdma_event_e40_sw_cleaned:
			break;
		case sdma_event_e50_hw_cleaned:
			break;
		case sdma_event_e60_hw_halted:
			break;
		case sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			break;
		case sdma_event_e80_hw_freeze:
			break;
		case sdma_event_e81_hw_frozen:
			sdma_set_state(sde, sdma_state_s82_freeze_sw_clean);
			sdma_start_sw_clean_up(sde);
			break;
		case sdma_event_e82_hw_unfreeze:
			break;
		case sdma_event_e85_link_down:
			break;
		case sdma_event_e90_sw_halted:
			break;
		}
		break;

	case sdma_state_s82_freeze_sw_clean:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			sdma_set_state(sde, sdma_state_s00_hw_down);
			sdma_start_sw_clean_up(sde);
			break;
		case sdma_event_e10_go_hw_start:
			break;
		case sdma_event_e15_hw_halt_done:
			break;
		case sdma_event_e25_hw_clean_up_done:
			break;
		case sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			break;
		case sdma_event_e40_sw_cleaned:
			/* notify caller this engine is done cleaning */
			atomic_dec(&sde->dd->sdma_unfreeze_count);
			wake_up_interruptible(&sde->dd->sdma_unfreeze_wq);
			break;
		case sdma_event_e50_hw_cleaned:
			break;
		case sdma_event_e60_hw_halted:
			break;
		case sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			break;
		case sdma_event_e80_hw_freeze:
			break;
		case sdma_event_e81_hw_frozen:
			break;
		case sdma_event_e82_hw_unfreeze:
			sdma_hw_start_up(sde);
			sdma_set_state(sde, ss->go_s99_running ?
				       sdma_state_s99_running :
				       sdma_state_s20_idle);
			break;
		case sdma_event_e85_link_down:
			break;
		case sdma_event_e90_sw_halted:
			break;
		}
		break;

	case sdma_state_s99_running:
		switch (event) {
		case sdma_event_e00_go_hw_down:
			sdma_set_state(sde, sdma_state_s00_hw_down);
			sdma_start_sw_clean_up(sde);
			break;
		case sdma_event_e10_go_hw_start:
			break;
		case sdma_event_e15_hw_halt_done:
			break;
		case sdma_event_e25_hw_clean_up_done:
			break;
		case sdma_event_e30_go_running:
			break;
		case sdma_event_e40_sw_cleaned:
			break;
		case sdma_event_e50_hw_cleaned:
			break;
		case sdma_event_e60_hw_halted:
			need_progress = 1;
			sdma_err_progress_check_schedule(sde);
		case sdma_event_e90_sw_halted:
			/*
			* SW initiated halt does not perform engines
			* progress check
			*/
			sdma_set_state(sde, sdma_state_s50_hw_halt_wait);
			sdma_start_err_halt_wait(sde);
			break;
		case sdma_event_e70_go_idle:
			sdma_set_state(sde, sdma_state_s60_idle_halt_wait);
			break;
		case sdma_event_e85_link_down:
			ss->go_s99_running = 0;
			/* fall through */
		case sdma_event_e80_hw_freeze:
			sdma_set_state(sde, sdma_state_s80_hw_freeze);
			atomic_dec(&sde->dd->sdma_unfreeze_count);
			wake_up_interruptible(&sde->dd->sdma_unfreeze_wq);
			break;
		case sdma_event_e81_hw_frozen:
			break;
		case sdma_event_e82_hw_unfreeze:
			break;
		}
		break;
	}

	ss->last_event = event;
	if (need_progress)
		sdma_make_progress(sde, 0);
}
