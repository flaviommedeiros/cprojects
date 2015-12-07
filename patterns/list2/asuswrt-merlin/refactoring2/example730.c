#ifdef CONFIG_DEBUG_VERBOSE
if (!ipipe_trap_notify(fp->seqstat & 0x3f, fp))
#endif
	{
		info.si_signo = sig;
		info.si_errno = 0;
		switch (trapnr) {
		case VEC_CPLB_VL:
		case VEC_MISALI_D:
		case VEC_CPLB_M:
		case VEC_CPLB_MHIT:
			info.si_addr = (void __user *)cpu_pda[cpu].dcplb_fault_addr;
			break;
		default:
			info.si_addr = (void __user *)fp->pc;
			break;
		}
		force_sig_info(sig, &info, current);
	}
