#ifdef CONFIG_PPC_TRANSACTIONAL_MEM
if (MSR_TM_ACTIVE(regs->msr)) {
		if (__put_user((unsigned long)&rt_sf->uc_transact,
			       &rt_sf->uc.uc_link)
		    || __put_user((unsigned long)tm_frame, &rt_sf->uc_transact.uc_regs))
			goto badframe;
	}
	else
#endif
		if (__put_user(0, &rt_sf->uc.uc_link))
			goto badframe;
