#ifdef CONFIG_PPC_TRANSACTIONAL_MEM
if (MSR_TM_ACTIVE(regs->msr)) {
		/* The ucontext_t passed to userland points to the second
		 * ucontext_t (for transactional state) with its uc_link ptr.
		 */
		err |= __put_user(&frame->uc_transact, &frame->uc.uc_link);
		err |= setup_tm_sigcontexts(&frame->uc.uc_mcontext,
					    &frame->uc_transact.uc_mcontext,
					    regs, ksig->sig,
					    NULL,
					    (unsigned long)ksig->ka.sa.sa_handler);
	} else
#endif
	{
		err |= __put_user(0, &frame->uc.uc_link);
		err |= setup_sigcontext(&frame->uc.uc_mcontext, regs, ksig->sig,
					NULL, (unsigned long)ksig->ka.sa.sa_handler,
					1);
	}
