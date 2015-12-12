switch (regnum) {
	case _IA64_REG_AR_KR0 ... _IA64_REG_AR_KR7:
		xen_set_kr(regnum - _IA64_REG_AR_KR0, val);
		break;
#ifdef CONFIG_IA32_SUPPORT
	case _IA64_REG_AR_EFLAG:
		xen_set_eflag(val);
		break;
#endif
	case _IA64_REG_AR_ITC:
		xen_set_itc(val);
		break;
	case _IA64_REG_CR_TPR:
		xen_set_tpr(val);
		break;
	case _IA64_REG_CR_ITM:
		xen_set_itm_with_offset(val);
		break;
	case _IA64_REG_CR_EOI:
		xen_eoi(val);
		break;
	default:
		ia64_native_setreg_func(regnum, val);
		break;
	}
