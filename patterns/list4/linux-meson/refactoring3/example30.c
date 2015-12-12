switch (action & ~CPU_TASKS_FROZEN) {

	case CPU_UP_PREPARE:
		rq->calc_load_update = calc_load_update;
		break;

	case CPU_ONLINE:
		/* Update our root-domain */
		raw_spin_lock_irqsave(&rq->lock, flags);
		if (rq->rd) {
			BUG_ON(!cpumask_test_cpu(cpu, rq->rd->span));

			set_rq_online(rq);
		}
		raw_spin_unlock_irqrestore(&rq->lock, flags);
		break;

#ifdef CONFIG_HOTPLUG_CPU
	case CPU_DYING:
		sched_ttwu_pending();
		/* Update our root-domain */
		raw_spin_lock_irqsave(&rq->lock, flags);
		if (rq->rd) {
			BUG_ON(!cpumask_test_cpu(cpu, rq->rd->span));
			set_rq_offline(rq);
		}
		migrate_tasks(cpu);
		BUG_ON(rq->nr_running != 1); /* the migration thread */
		raw_spin_unlock_irqrestore(&rq->lock, flags);
		break;

	case CPU_DEAD:
		calc_load_migrate(rq);
		break;
#endif
	}
