switch (ps->type) {
		case SCHEDP_RPRIO:
		case SCHEDP_RLPRIO:
			/* The relative priority has been converted to absolute priority in relative_prio_convert(). */
			prio = ps->value;
			/* FIXME: When the IPI handling thread is
			 * creating a thread (requested by a remote
			 * core) , since we can't copy accounting info
			 * from the actual parent (which is on a
			 * different core), we zero the accounting
			 * info instead of touching remote
			 * data-structures. */
			if (sched_curr_is_IPI_handler())
				sched_clear_accounting(t);
			else
				memcpy(sched_get_accounting(t), sched_get_accounting(c), sizeof(struct sched_accounting));
#ifdef DEFERRABLE
			if (sched_get_accounting(t)->T) ADD_LIST(&PERCPU_GET(fprr_state)->servers, t, sched_next, sched_prev);
#endif
			if (prio > PRIO_LOWEST) prio = PRIO_LOWEST;
			break;
		case SCHEDP_PRIO:
			/* absolute priority */
			prio = ps->value;
			break;
		case SCHEDP_IDLE:
			/* idle thread */
			prio = PRIO_LOWEST;
			break;
		case SCHEDP_INIT:
			/* idle thread */
			prio = PRIO_LOW;
			break;
		case SCHEDP_TIMER:
			/* timer thread */
			prio = PRIO_HIGHEST;
			break;
		case SCHEDP_IPI_HANDLER:
			prio = IPI_HANDLER_PRIO;
			break;
		case SCHEDP_CORE_ID:
			assert(ps->value == cos_cpuid());
			break;
#ifdef DEFERRABLE
		case SCHEDP_BUDGET:
			prio = sched_get_metric(t)->priority;
			sched_get_accounting(t)->C = ps->value;
			sched_get_accounting(t)->C_used = 0;
			fp_move_end_runnable(t);
			break;
		case SCHEDP_WINDOW:
			prio = sched_get_metric(t)->priority;
			sched_get_accounting(t)->T = ps->value;
			sched_get_accounting(t)->T_exp = 0;
			if (EMPTY_LIST(t, sched_next, sched_prev) && 
			    sched_get_accounting(t)->T) {
				ADD_LIST(&PERCPU_GET(fprr_state)->servers, t, sched_next, sched_prev);
			}
			fp_move_end_runnable(t);
			break;
#endif
		default:
			printc("fprr: core %ld received unknown priority option\n", cos_cpuid());
			prio = PRIO_LOW;
		}
