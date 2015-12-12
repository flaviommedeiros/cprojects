switch (curr) {
	case 'r':
		/* priority relative to current thread */
		c = sched_get_current();
		assert(c);
		tmp = atoi(&p[1]);
		prio = sched_get_metric(c)->priority + tmp;
		memcpy(sched_get_accounting(t), sched_get_accounting(c), sizeof(struct sched_accounting));
#ifdef DEFERRABLE
		if (sched_get_accounting(t)->T) ADD_LIST(&PERCPU_GET(fprr_state)->servers, t, sched_next, sched_prev);
#endif

		if (prio > PRIO_LOWEST) prio = PRIO_LOWEST;
		break;
	case 'a':
		/* absolute priority */
		prio = atoi(&p[1]);
		break;
	case 'i':
		/* idle thread */
		prio = PRIO_LOWEST;
		break;
	case 't':
		/* timer thread */
		prio = PRIO_HIGHEST;
		break;
#ifdef DEFERRABLE
	case 'd':
	{
		prio = ds_parse_params(t, p);
		if (EMPTY_LIST(t, sched_next, sched_prev) && 
		    sched_get_accounting(t)->T) {
			ADD_LIST(&PERCPU_GET(fprr_state)->servers, t, sched_next, sched_prev);
		}
		fp_move_end_runnable(t);
		break;
	}
#endif
	default:
		printc("unknown priority option @ %s, setting to low\n", p);
		prio = PRIO_LOW;
	}
