switch (state.event) {
#ifdef CONFIG_SUSPEND
	case PM_EVENT_SUSPEND:
		return ops->suspend;
	case PM_EVENT_RESUME:
		return ops->resume;
#endif /* CONFIG_SUSPEND */
#ifdef CONFIG_HIBERNATE_CALLBACKS
	case PM_EVENT_FREEZE:
	case PM_EVENT_QUIESCE:
		if (ops->freeze)
			return ops->freeze;
		else
			return ops->suspend;
	case PM_EVENT_HIBERNATE:
		return ops->poweroff;
	case PM_EVENT_THAW:
	case PM_EVENT_RECOVER:
		if (ops->thaw)
			return ops->thaw;
		else
			return ops->resume;
		break;
	case PM_EVENT_RESTORE:
		if (ops->restore)
			return ops->restore;
		else
			return ops->resume;
#endif /* CONFIG_HIBERNATE_CALLBACKS */
	}
