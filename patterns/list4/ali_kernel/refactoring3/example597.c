switch (regnum) {
	case _IA64_REG_PSR:
		res = xen_get_psr();
		break;
#ifdef CONFIG_IA32_SUPPORT
	case _IA64_REG_AR_EFLAG:
		res = xen_get_eflag();
		break;
#endif
	case _IA64_REG_AR_ITC:
		res = xen_get_itc();
		break;
	case _IA64_REG_CR_ITM:
		res = xen_get_itm_with_offset();
		break;
	case _IA64_REG_CR_IVR:
		res = xen_get_ivr();
		break;
	case _IA64_REG_CR_TPR:
		res = xen_get_tpr();
		break;
	default:
		res = ia64_native_getreg_func(regnum);
		break;
	}
