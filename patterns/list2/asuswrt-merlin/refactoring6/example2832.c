if (!tsk->mm || atomic_read(&tsk->mm->mm_users) > 1 ||
#ifdef CONFIG_AIO
	    !hlist_empty(&tsk->mm->ioctx_list) ||
#endif
	    tsk->mm != tsk->active_mm) {
		task_unlock(tsk);
		return -EINVAL;
	}
