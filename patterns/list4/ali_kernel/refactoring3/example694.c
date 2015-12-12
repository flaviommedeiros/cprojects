switch(ntohl(status)) {
	case NLM_LCK_GRANTED:
		return 0;
	case NLM_LCK_DENIED:
		return -EAGAIN;
	case NLM_LCK_DENIED_NOLOCKS:
	case NLM_LCK_DENIED_GRACE_PERIOD:
		return -ENOLCK;
	case NLM_LCK_BLOCKED:
		printk(KERN_NOTICE "lockd: unexpected status NLM_BLOCKED\n");
		return -ENOLCK;
#ifdef CONFIG_LOCKD_V4
	case NLM_DEADLCK:
		return -EDEADLK;
	case NLM_ROFS:
		return -EROFS;
	case NLM_STALE_FH:
		return -ESTALE;
	case NLM_FBIG:
		return -EOVERFLOW;
	case NLM_FAILED:
		return -ENOLCK;
#endif
	}
