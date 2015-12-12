switch (args->arg0) {
	case LHCALL_FLUSH_ASYNC:
		/*
		 * This call does nothing, except by breaking out of the Guest
		 * it makes us process all the asynchronous hypercalls.
		 */
		break;
	case LHCALL_SEND_INTERRUPTS:
		/*
		 * This call does nothing too, but by breaking out of the Guest
		 * it makes us process any pending interrupts.
		 */
		break;
	case LHCALL_LGUEST_INIT:
		/*
		 * You can't get here unless you're already initialized.  Don't
		 * do that.
		 */
		kill_guest(cpu, "already have lguest_data");
		break;
	case LHCALL_SHUTDOWN: {
		char msg[128];
		/*
		 * Shutdown is such a trivial hypercall that we do it in five
		 * lines right here.
		 *
		 * If the lgread fails, it will call kill_guest() itself; the
		 * kill_guest() with the message will be ignored.
		 */
		__lgread(cpu, msg, args->arg1, sizeof(msg));
		msg[sizeof(msg)-1] = '\0';
		kill_guest(cpu, "CRASH: %s", msg);
		if (args->arg2 == LGUEST_SHUTDOWN_RESTART)
			cpu->lg->dead = ERR_PTR(-ERESTART);
		break;
	}
	case LHCALL_FLUSH_TLB:
		/* FLUSH_TLB comes in two flavors, depending on the argument: */
		if (args->arg1)
			guest_pagetable_clear_all(cpu);
		else
			guest_pagetable_flush_user(cpu);
		break;

	/*
	 * All these calls simply pass the arguments through to the right
	 * routines.
	 */
	case LHCALL_NEW_PGTABLE:
		guest_new_pagetable(cpu, args->arg1);
		break;
	case LHCALL_SET_STACK:
		guest_set_stack(cpu, args->arg1, args->arg2, args->arg3);
		break;
	case LHCALL_SET_PTE:
#ifdef CONFIG_X86_PAE
		guest_set_pte(cpu, args->arg1, args->arg2,
				__pte(args->arg3 | (u64)args->arg4 << 32));
#else
		guest_set_pte(cpu, args->arg1, args->arg2, __pte(args->arg3));
#endif
		break;
	case LHCALL_SET_PGD:
		guest_set_pgd(cpu->lg, args->arg1, args->arg2);
		break;
#ifdef CONFIG_X86_PAE
	case LHCALL_SET_PMD:
		guest_set_pmd(cpu->lg, args->arg1, args->arg2);
		break;
#endif
	case LHCALL_SET_CLOCKEVENT:
		guest_set_clockevent(cpu, args->arg1);
		break;
	case LHCALL_TS:
		/* This sets the TS flag, as we saw used in run_guest(). */
		cpu->ts = args->arg1;
		break;
	case LHCALL_HALT:
		/* Similarly, this sets the halted flag for run_guest(). */
		cpu->halted = 1;
		break;
	case LHCALL_NOTIFY:
		cpu->pending_notify = args->arg1;
		break;
	default:
		/* It should be an architecture-specific hypercall. */
		if (lguest_arch_do_hcall(cpu, args))
			kill_guest(cpu, "Bad hypercall %li\n", args->arg0);
	}
