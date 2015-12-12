switch (request) {
#ifdef PTRACE_SINGLEBLOCK
	case PTRACE_SINGLEBLOCK:
		if (unlikely(!arch_has_block_step()))
			return -EIO;
		action = UTRACE_BLOCKSTEP;
		events |= UTRACE_EVENT(SYSCALL_EXIT);
		break;
#endif

#ifdef PTRACE_SINGLESTEP
	case PTRACE_SINGLESTEP:
		if (unlikely(!arch_has_single_step()))
			return -EIO;
		action = UTRACE_SINGLESTEP;
		events |= UTRACE_EVENT(SYSCALL_EXIT);
		break;
#endif

#ifdef PTRACE_SYSEMU
	case PTRACE_SYSEMU_SINGLESTEP:
		if (unlikely(!arch_has_single_step()))
			return -EIO;
		action = UTRACE_SINGLESTEP;
	case PTRACE_SYSEMU:
		ctx->options |= PTRACE_O_SYSEMU;
		events |= UTRACE_EVENT(SYSCALL_ENTRY);
		break;
#endif

	case PTRACE_SYSCALL:
		events |= UTRACE_EVENT_SYSCALL;
		break;

	case PTRACE_CONT:
		break;
	default:
		return -EIO;
	}
