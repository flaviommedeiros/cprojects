switch (*insn) {
	case 0x9c:	/* pushfl */
		*tos &= ~(X86_EFLAGS_TF | X86_EFLAGS_IF);
		*tos |= kcb->kprobe_old_flags;
		break;
	case 0xc2:	/* iret/ret/lret */
	case 0xc3:
	case 0xca:
	case 0xcb:
	case 0xcf:
	case 0xea:	/* jmp absolute -- ip is correct */
		/* ip is already adjusted, no more changes required */
		p->ainsn.boostable = 1;
		goto no_change;
	case 0xe8:	/* call relative - Fix return addr */
		*tos = orig_ip + (*tos - copy_ip);
		break;
#ifdef CONFIG_X86_32
	case 0x9a:	/* call absolute -- same as call absolute, indirect */
		*tos = orig_ip + (*tos - copy_ip);
		goto no_change;
#endif
	case 0xff:
		if ((insn[1] & 0x30) == 0x10) {
			/*
			 * call absolute, indirect
			 * Fix return addr; ip is correct.
			 * But this is not boostable
			 */
			*tos = orig_ip + (*tos - copy_ip);
			goto no_change;
		} else if (((insn[1] & 0x31) == 0x20) ||
			   ((insn[1] & 0x31) == 0x21)) {
			/*
			 * jmp near and far, absolute indirect
			 * ip is correct. And this is boostable
			 */
			p->ainsn.boostable = 1;
			goto no_change;
		}
	default:
		break;
	}
