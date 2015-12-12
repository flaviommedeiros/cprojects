switch(uc->cmd) {
	case UC_SETVERBOSE:
	case UC_SETSYNC:
	case UC_SETTAGS:
	case UC_SETWIDE:
		SKIP_SPACES(ptr, len);
		GET_INT_ARG(ptr, len, uc->data);
#ifdef DEBUG_PROC_INFO
printk("sym_user_command: data=%ld\n", uc->data);
#endif
		break;
#ifdef SYM_LINUX_DEBUG_CONTROL_SUPPORT
	case UC_SETDEBUG:
		while (len > 0) {
			SKIP_SPACES(ptr, len);
			if	((arg_len = is_keyword(ptr, len, "alloc")))
				uc->data |= DEBUG_ALLOC;
			else if	((arg_len = is_keyword(ptr, len, "phase")))
				uc->data |= DEBUG_PHASE;
			else if	((arg_len = is_keyword(ptr, len, "queue")))
				uc->data |= DEBUG_QUEUE;
			else if	((arg_len = is_keyword(ptr, len, "result")))
				uc->data |= DEBUG_RESULT;
			else if	((arg_len = is_keyword(ptr, len, "scatter")))
				uc->data |= DEBUG_SCATTER;
			else if	((arg_len = is_keyword(ptr, len, "script")))
				uc->data |= DEBUG_SCRIPT;
			else if	((arg_len = is_keyword(ptr, len, "tiny")))
				uc->data |= DEBUG_TINY;
			else if	((arg_len = is_keyword(ptr, len, "timing")))
				uc->data |= DEBUG_TIMING;
			else if	((arg_len = is_keyword(ptr, len, "nego")))
				uc->data |= DEBUG_NEGO;
			else if	((arg_len = is_keyword(ptr, len, "tags")))
				uc->data |= DEBUG_TAGS;
			else if	((arg_len = is_keyword(ptr, len, "pointer")))
				uc->data |= DEBUG_POINTER;
			else
				return -EINVAL;
			ptr += arg_len; len -= arg_len;
		}
#ifdef DEBUG_PROC_INFO
printk("sym_user_command: data=%ld\n", uc->data);
#endif
		break;
#endif /* SYM_LINUX_DEBUG_CONTROL_SUPPORT */
	case UC_SETFLAG:
		while (len > 0) {
			SKIP_SPACES(ptr, len);
			if	((arg_len = is_keyword(ptr, len, "no_disc")))
				uc->data &= ~SYM_DISC_ENABLED;
			else
				return -EINVAL;
			ptr += arg_len; len -= arg_len;
		}
		break;
	default:
		break;
	}
