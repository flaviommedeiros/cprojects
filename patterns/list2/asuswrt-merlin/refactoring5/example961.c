#ifdef CONFIG_SMP
if (p == task_rq(p)->migration_thread)
			/*
			 * The migration thread does the actual balancing.
			 * Giving its load any weight will skew balancing
			 * adversely.
			 */
			p->load_weight = 0;
		else
#endif
			p->load_weight = RTPRIO_TO_LOAD_WEIGHT(p->rt_priority);
