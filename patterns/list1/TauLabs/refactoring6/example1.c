if (PIOS_heap_malloc_failed_p()
	     || (stats.HeapRemaining < HEAP_LIMIT_CRITICAL)
#if !defined(ARCH_POSIX) && !defined(ARCH_WIN32) && defined(CHECK_IRQ_STACK)
	     || (stats.IRQStackRemaining < IRQSTACK_LIMIT_CRITICAL)
#endif
	    ) {
		AlarmsSet(SYSTEMALARMS_ALARM_OUTOFMEMORY, SYSTEMALARMS_ALARM_CRITICAL);
	} else if (
		(stats.HeapRemaining < HEAP_LIMIT_WARNING)
#if !defined(ARCH_POSIX) && !defined(ARCH_WIN32) && defined(CHECK_IRQ_STACK)
	     || (stats.IRQStackRemaining < IRQSTACK_LIMIT_WARNING)
#endif
	    ) {
		AlarmsSet(SYSTEMALARMS_ALARM_OUTOFMEMORY, SYSTEMALARMS_ALARM_WARNING);
	} else {
		AlarmsClear(SYSTEMALARMS_ALARM_OUTOFMEMORY);
	}
