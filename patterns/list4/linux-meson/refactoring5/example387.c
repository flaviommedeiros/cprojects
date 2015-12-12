#ifdef CONFIG_PREEMPT
if (tid_to_cpu(tid) != tid_to_cpu(actual_tid))
		printk("due to cpu change %d -> %d\n",
			tid_to_cpu(tid), tid_to_cpu(actual_tid));
	else
#endif
	if (tid_to_event(tid) != tid_to_event(actual_tid))
		printk("due to cpu running other code. Event %ld->%ld\n",
			tid_to_event(tid), tid_to_event(actual_tid));
	else
		printk("for unknown reason: actual=%lx was=%lx target=%lx\n",
			actual_tid, tid, next_tid(tid));
