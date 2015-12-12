#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,27))
if (tsk->flags & PF_KTHREAD)
#else
		if (tsk->flags & PF_BORROWED_MM)
#endif
			return ret;
