#ifdef CONFIG_DEBUG_VERBOSE
if (!ipipe_trap_notify(fp->seqstat & 0x3f, fp))
#endif
	{
		info.si_signo = sig;
		info.si_errno = 0;
		info.si_addr = (void __user *)fp->pc;
		force_sig_info(sig, &info, current);
	}
