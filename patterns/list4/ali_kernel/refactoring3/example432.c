switch (no) {
	case arg_AX:
		rv = &regs->ax;
		break;
	case arg_BX:
		rv = &regs->bx;
		break;
	case arg_CX:
		rv = &regs->cx;
		break;
	case arg_DX:
		rv = &regs->dx;
		break;
	case arg_SP:
		rv = &regs->sp;
		break;
	case arg_BP:
		rv = &regs->bp;
		break;
	case arg_SI:
		rv = &regs->si;
		break;
	case arg_DI:
		rv = &regs->di;
		break;
#ifdef __amd64__
	case arg_R8:
		rv = &regs->r8;
		break;
	case arg_R9:
		rv = &regs->r9;
		break;
	case arg_R10:
		rv = &regs->r10;
		break;
	case arg_R11:
		rv = &regs->r11;
		break;
	case arg_R12:
		rv = &regs->r12;
		break;
	case arg_R13:
		rv = &regs->r13;
		break;
	case arg_R14:
		rv = &regs->r14;
		break;
	case arg_R15:
		rv = &regs->r15;
		break;
#endif
	default:
		printk(KERN_ERR "mmiotrace: Error reg no# %d\n", no);
	}
