switch(listnr) {
	default:
		goto exit_err;
#ifdef CONFIG_AUDITSYSCALL
	case AUDIT_FILTER_ENTRY:
		if (rule->action == AUDIT_ALWAYS)
			goto exit_err;
	case AUDIT_FILTER_EXIT:
	case AUDIT_FILTER_TASK:
#endif
	case AUDIT_FILTER_USER:
	case AUDIT_FILTER_TYPE:
		;
	}
