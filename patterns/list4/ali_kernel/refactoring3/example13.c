switch (action & ~CPU_TASKS_FROZEN) {
	case CPU_UP_PREPARE:
		BUG_ON(stopper->thread || stopper->enabled ||
		       !list_empty(&stopper->works));
		p = kthread_create(cpu_stopper_thread, stopper, "migration/%d",
				   cpu);
		if (IS_ERR(p))
			return NOTIFY_BAD;
		sched_setscheduler_nocheck(p, SCHED_FIFO, &param);
		get_task_struct(p);
		stopper->thread = p;
		break;

	case CPU_ONLINE:
		kthread_bind(stopper->thread, cpu);
		/* strictly unnecessary, as first user will wake it */
		wake_up_process(stopper->thread);
		/* mark enabled */
		spin_lock_irq(&stopper->lock);
		stopper->enabled = true;
		spin_unlock_irq(&stopper->lock);
		break;

#ifdef CONFIG_HOTPLUG_CPU
	case CPU_UP_CANCELED:
	case CPU_POST_DEAD:
	{
		struct cpu_stop_work *work;

		/* kill the stopper */
		kthread_stop(stopper->thread);
		/* drain remaining works */
		spin_lock_irq(&stopper->lock);
		list_for_each_entry(work, &stopper->works, list)
			cpu_stop_signal_done(work->done, false);
		stopper->enabled = false;
		spin_unlock_irq(&stopper->lock);
		/* release the stopper */
		put_task_struct(stopper->thread);
		stopper->thread = NULL;
		break;
	}
#endif
	}
