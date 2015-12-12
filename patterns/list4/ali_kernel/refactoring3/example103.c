switch (cs->mode) {
			case M_UNIMODEM:
				cs->at_state.pending_commands |= PC_CIDMODE;
				gig_dbg(DEBUG_CMD, "Scheduling PC_CIDMODE");
				cs->commands_pending = 1;
				return;
#ifdef GIG_MAYINITONDIAL
			case M_UNKNOWN:
				schedule_init(cs, MS_INIT);
				return;
#endif
			}
