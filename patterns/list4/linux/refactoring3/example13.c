switch (mode) {
	case SECCOMP_MODE_STRICT:
		__secure_computing_strict(this_syscall);  /* may call do_exit */
		return SECCOMP_PHASE1_OK;
#ifdef CONFIG_SECCOMP_FILTER
	case SECCOMP_MODE_FILTER:
		return __seccomp_phase1_filter(this_syscall, sd);
#endif
	default:
		BUG();
	}
