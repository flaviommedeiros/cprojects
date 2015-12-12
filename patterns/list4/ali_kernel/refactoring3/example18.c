switch (action) {

	case CPU_UP_PREPARE:
	case CPU_UP_PREPARE_FROZEN:
		p = kthread_create(migration_thread, hcpu, "migration/%d", cpu);
		if (IS_ERR(p))
			return NOTIFY_BAD;
		kthread_bind(p, cpu);
		/* Must be high prio: stop_machine expects to yield to it. */
		rq = task_rq_lock(p, &flags);
		__setscheduler(rq, p, SCHED_FIFO, MAX_RT_PRIO-1);
		task_rq_unlock(rq, &flags);
		get_task_struct(p);
		cpu_rq(cpu)->migration_thread = p;
		rq->calc_load_update = calc_load_update;
		break;

	case CPU_ONLINE:
	case CPU_ONLINE_FROZEN:
		/* Strictly unnecessary, as first user will wake it. */
		wake_up_process(cpu_rq(cpu)->migration_thread);

		/* Update our root-domain */
		rq = cpu_rq(cpu);
		spin_lock_irqsave(&rq->lock, flags);
		if (rq->rd) {
			BUG_ON(!cpumask_test_cpu(cpu, rq->rd->span));

			set_rq_online(rq);
		}
		spin_unlock_irqrestore(&rq->lock, flags);
		break;

#ifdef CONFIG_HOTPLUG_CPU
	case CPU_UP_CANCELED:
	case CPU_UP_CANCELED_FROZEN:
		if (!cpu_rq(cpu)->migration_thread)
			break;
		/* Unbind it from offline cpu so it can run. Fall thru. */
		kthread_bind(cpu_rq(cpu)->migration_thread,
			     cpumask_any(cpu_online_mask));
		kthread_stop(cpu_rq(cpu)->migration_thread);
		put_task_struct(cpu_rq(cpu)->migration_thread);
		cpu_rq(cpu)->migration_thread = NULL;
		break;

	case CPU_POST_DEAD:
		/*
		 * Bring the migration thread down in CPU_POST_DEAD event,
		 * since the timers should have got migrated by now and thus
		 * we should not see a deadlock between trying to kill the
		 * migration thread and the sched_rt_period_timer.
		 */
		rq = cpu_rq(cpu);
		kthread_stop(rq->migration_thread);
		put_task_struct(rq->migration_thread);
		rq->migration_thread = NULL;
		break;

	case CPU_DEAD:
	case CPU_DEAD_FROZEN:
		migrate_live_tasks(cpu);
		rq = cpu_rq(cpu);
		/* Idle task back to normal (off runqueue, low prio) */
		spin_lock_irq(&rq->lock);
		deactivate_task(rq, rq->idle, 0);
		__setscheduler(rq, rq->idle, SCHED_NORMAL, 0);
		rq->idle->sched_class = &idle_sched_class;
		migrate_dead_tasks(cpu);
		spin_unlock_irq(&rq->lock);
		migrate_nr_uninterruptible(rq);
		BUG_ON(rq->nr_running != 0);
		calc_global_load_remove(rq);
		/*
		 * No need to migrate the tasks: it was best-effort if
		 * they didn't take sched_hotcpu_mutex. Just wake up
		 * the requestors.
		 */
		spin_lock_irq(&rq->lock);
		while (!list_empty(&rq->migration_queue)) {
			struct migration_req *req;

			req = list_entry(rq->migration_queue.next,
					 struct migration_req, list);
			list_del_init(&req->list);
			spin_unlock_irq(&rq->lock);
			complete(&req->done);
			spin_lock_irq(&rq->lock);
		}
		spin_unlock_irq(&rq->lock);
		break;

	case CPU_DYING:
	case CPU_DYING_FROZEN:
		/* Update our root-domain */
		rq = cpu_rq(cpu);
		spin_lock_irqsave(&rq->lock, flags);
		if (rq->rd) {
			BUG_ON(!cpumask_test_cpu(cpu, rq->rd->span));
			set_rq_offline(rq);
		}
		spin_unlock_irqrestore(&rq->lock, flags);
		break;
#endif
	}
