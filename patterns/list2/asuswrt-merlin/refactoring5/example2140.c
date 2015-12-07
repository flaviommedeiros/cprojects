#ifdef CONFIG_COMPAT
if (compat)
		len = sizeof(struct dlm_lock_result32);
	else
#endif
		len = sizeof(struct dlm_lock_result);
