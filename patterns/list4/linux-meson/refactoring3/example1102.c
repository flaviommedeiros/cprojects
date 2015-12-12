switch (type & 0x1F) {
	case MICROBLAZE_ILL_OPCODE_EXCEPTION:
		if (user_mode(regs)) {
			pr_debug("Illegal opcode exception in user mode\n");
			_exception(SIGILL, regs, ILL_ILLOPC, addr);
			return;
		}
		pr_warn("Illegal opcode exception in kernel mode.\n");
		die("opcode exception", regs, SIGBUS);
		break;
	case MICROBLAZE_IBUS_EXCEPTION:
		if (user_mode(regs)) {
			pr_debug("Instruction bus error exception in user mode\n");
			_exception(SIGBUS, regs, BUS_ADRERR, addr);
			return;
		}
		pr_warn("Instruction bus error exception in kernel mode.\n");
		die("bus exception", regs, SIGBUS);
		break;
	case MICROBLAZE_DBUS_EXCEPTION:
		if (user_mode(regs)) {
			pr_debug("Data bus error exception in user mode\n");
			_exception(SIGBUS, regs, BUS_ADRERR, addr);
			return;
		}
		pr_warn("Data bus error exception in kernel mode.\n");
		die("bus exception", regs, SIGBUS);
		break;
	case MICROBLAZE_DIV_ZERO_EXCEPTION:
		if (user_mode(regs)) {
			pr_debug("Divide by zero exception in user mode\n");
			_exception(SIGFPE, regs, FPE_INTDIV, addr);
			return;
		}
		pr_warn("Divide by zero exception in kernel mode.\n");
		die("Divide by zero exception", regs, SIGBUS);
		break;
	case MICROBLAZE_FPU_EXCEPTION:
		pr_debug("FPU exception\n");
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
		pr_debug("Privileged exception\n");
		_exception(SIGILL, regs, ILL_PRVOPC, addr);
		break;
#endif
	default:
	/* FIXME what to do in unexpected exception */
		pr_warn("Unexpected exception %02x PC=%08x in %s mode\n",
			type, (unsigned int) addr,
			kernel_mode(regs) ? "kernel" : "user");
	}
