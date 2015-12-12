switch (action & ~CPU_TASKS_FROZEN) {
	case CPU_UP_PREPARE:
		BUG_ON(stopper->thread || stopper->enabled ||
		       !list_empty(&stopper->works));
		p = kthread_create_on_node(cpu_stopper_thread,
					   stopper,
					   cpu_to_node(cpu),
					   "migration/%d", cpu);
		if (IS_ERR(p))
			return notifier_from_errno(PTR_ERR(p));
		get_task_struct(p);
		kthread_bind(p, cpu);
		sched_set_stop_task(cpu, p);
		stopper->thread = p;
		break;

	case CPU_ONLINE:
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

		sched_set_stop_task(cpu, NULL);
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
