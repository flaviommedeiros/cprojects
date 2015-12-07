#ifndef FEATURE_MDDI_DISABLE_REVERSE
if (pmhctl->llist_info.reg_read_waiting) {
			if (pmhctl->rev_state == MDDI_REV_IDLE) {
				/*
				 * we have a register read to send and
				 * can send it now
				 */
				pmhctl->rev_state = MDDI_REV_REG_READ_ISSUED;
				mddi_reg_read_retry = 0;
				first_pkt_index =
				    pmhctl->llist_info.waiting_start_idx;
				pmhctl->llist_info.reg_read_waiting = FALSE;
			}
		} else
#endif
		{
			/*
			 * not register read to worry about, go ahead and write
			 * anything that may be on the waiting list.
			 */
			first_pkt_index = pmhctl->llist_info.waiting_start_idx;
		}
