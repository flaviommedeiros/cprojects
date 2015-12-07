if (time_after_eq(jiffies, rq->next_balance) &&
	    likely(!on_null_domain(cpu)))
		raise_softirq(SCHED_SOFTIRQ);
#ifdef CONFIG_NO_HZ
	else if (nohz_kick_needed(rq, cpu) && likely(!on_null_domain(cpu)))
		nohz_balancer_kick(cpu);
#endif
