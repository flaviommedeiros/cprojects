#ifdef CONFIG_FAIR_GROUP_SCHED
if (tsk->sched_class->task_move_group)
		tsk->sched_class->task_move_group(tsk);
	else
#endif
		set_task_rq(tsk, task_cpu(tsk));
