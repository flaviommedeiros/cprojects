switch (state.event) {
#ifdef CONFIG_SUSPEND
	case PM_EVENT_SUSPEND:
		return ops->suspend_noirq;
	case PM_EVENT_RESUME:
		return ops->resume_noirq;
#endif /* CONFIG_SUSPEND */
#ifdef CONFIG_HIBERNATE_CALLBACKS
	case PM_EVENT_FREEZE:
	case PM_EVENT_QUIESCE:
		return ops->freeze_noirq;
	case PM_EVENT_HIBERNATE:
		return ops->poweroff_noirq;
	case PM_EVENT_THAW:
	case PM_EVENT_RECOVER:
		return ops->thaw_noirq;
	case PM_EVENT_RESTORE:
		return ops->restore_noirq;
#endif /* CONFIG_HIBERNATE_CALLBACKS */
	}
