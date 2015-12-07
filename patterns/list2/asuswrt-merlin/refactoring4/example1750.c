#ifdef CONFIG_COMPAT
if (count < sizeof(struct dlm_lock_result32))
#else
	if (count < sizeof(struct dlm_lock_result))
#endif
		return -EINVAL;
