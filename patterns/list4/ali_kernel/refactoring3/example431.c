switch (no) {
	case arg_AL:
		rv = (unsigned char *)&regs->ax;
		break;
	case arg_BL:
		rv = (unsigned char *)&regs->bx;
		break;
	case arg_CL:
		rv = (unsigned char *)&regs->cx;
		break;
	case arg_DL:
		rv = (unsigned char *)&regs->dx;
		break;
#ifdef __amd64__
	case arg_R8:
		rv = (unsigned char *)&regs->r8;
		break;
	case arg_R9:
		rv = (unsigned char *)&regs->r9;
		break;
	case arg_R10:
		rv = (unsigned char *)&regs->r10;
		break;
	case arg_R11:
		rv = (unsigned char *)&regs->r11;
		break;
	case arg_R12:
		rv = (unsigned char *)&regs->r12;
		break;
	case arg_R13:
		rv = (unsigned char *)&regs->r13;
		break;
	case arg_R14:
		rv = (unsigned char *)&regs->r14;
		break;
	case arg_R15:
		rv = (unsigned char *)&regs->r15;
		break;
#endif
	default:
		break;
	}
