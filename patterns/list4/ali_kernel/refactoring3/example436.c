switch (type & 0x1F) {
	case MICROBLAZE_ILL_OPCODE_EXCEPTION:
		if (user_mode(regs)) {
			pr_debug(KERN_WARNING "Illegal opcode exception " \
							"in user mode.\n");
			_exception(SIGILL, regs, ILL_ILLOPC, addr);
			return;
		}
		printk(KERN_WARNING "Illegal opcode exception " \
							"in kernel mode.\n");
		die("opcode exception", regs, SIGBUS);
		break;
	case MICROBLAZE_IBUS_EXCEPTION:
		if (user_mode(regs)) {
			pr_debug(KERN_WARNING "Instruction bus error " \
						"exception in user mode.\n");
			_exception(SIGBUS, regs, BUS_ADRERR, addr);
			return;
		}
		printk(KERN_WARNING "Instruction bus error exception " \
							"in kernel mode.\n");
		die("bus exception", regs, SIGBUS);
		break;
	case MICROBLAZE_DBUS_EXCEPTION:
		if (user_mode(regs)) {
			pr_debug(KERN_WARNING "Data bus error exception " \
							"in user mode.\n");
			_exception(SIGBUS, regs, BUS_ADRERR, addr);
			return;
		}
		printk(KERN_WARNING "Data bus error exception " \
							"in kernel mode.\n");
		die("bus exception", regs, SIGBUS);
		break;
	case MICROBLAZE_DIV_ZERO_EXCEPTION:
		if (user_mode(regs)) {
			pr_debug(KERN_WARNING "Divide by zero exception " \
							"in user mode\n");
			_exception(SIGILL, regs, FPE_INTDIV, addr);
			return;
		}
		printk(KERN_WARNING "Divide by zero exception " \
							"in kernel mode.\n");
		die("Divide by exception", regs, SIGBUS);
		break;
	case MICROBLAZE_FPU_EXCEPTION:
		pr_debug(KERN_WARNING "FPU exception\n");
		/* IEEE FP exception */
		/* I removed fsr variable and use code var for storing fsr */
		if (fsr & FSR_IO)
			fsr = FPE_FLTINV;
		else if (fsr & FSR_OF)
			fsr = FPE_FLTOVF;
		else if (fsr & FSR_UF)
			fsr = FPE_FLTUND;
		else if (fsr & FSR_DZ)
			fsr = FPE_FLTDIV;
		else if (fsr & FSR_DO)
			fsr = FPE_FLTRES;
		_exception(SIGFPE, regs, fsr, addr);
		break;

#ifdef CONFIG_MMU
	case MICROBLAZE_PRIVILEGED_EXCEPTION:
		pr_debug(KERN_WARNING "Privileged exception\n");
		/* "brk r0,r0" - used as debug breakpoint */
		if (get_user(code, (unsigned long *)regs->pc) == 0
			&& code == 0x980c0000) {
			_exception(SIGTRAP, regs, TRAP_BRKPT, addr);
		} else {
			_exception(SIGILL, regs, ILL_PRVOPC, addr);
		}
		break;
#endif
	default:
	/* FIXME what to do in unexpected exception */
		printk(KERN_WARNING "Unexpected exception %02x "
			"PC=%08x in %s mode\n", type, (unsigned int) addr,
			kernel_mode(regs) ? "kernel" : "user");
	}
