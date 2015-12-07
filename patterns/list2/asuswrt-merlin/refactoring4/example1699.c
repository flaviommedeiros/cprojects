#ifdef CONFIG_COMPAT
if (count < sizeof(struct dlm_write_request32))
#else
	if (count < sizeof(struct dlm_write_request))
#endif
		return -EINVAL;
