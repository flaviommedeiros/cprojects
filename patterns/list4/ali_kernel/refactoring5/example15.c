#ifdef CONFIG_TN3270_CONSOLE
if (raw3270_registered == 0) {
		unsigned long flags;

		spin_lock_irqsave(get_ccwdev_lock(rp->cdev), flags);
		while (!test_and_clear_bit(RAW3270_FLAGS_ATTN, &rp->flags))
			wait_cons_dev();
		spin_unlock_irqrestore(get_ccwdev_lock(rp->cdev), flags);
	} else
#endif
		rc = wait_event_interruptible(raw3270_wait_queue,
			test_and_clear_bit(RAW3270_FLAGS_ATTN, &rp->flags));
