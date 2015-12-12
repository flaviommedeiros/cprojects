switch(listnr) {
	default:
		goto exit_err;
	case AUDIT_FILTER_USER:
	case AUDIT_FILTER_TYPE:
#ifdef CONFIG_AUDITSYSCALL
	case AUDIT_FILTER_ENTRY:
	case AUDIT_FILTER_EXIT:
	case AUDIT_FILTER_TASK:
#endif
		;
	}
