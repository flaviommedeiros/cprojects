#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,30))
if (gtp_have_step || gtp_have_watch_tracepoint)
#else
	if (gtp_have_step)
#endif
		unregister_die_notifier(&gtp_notifier);
