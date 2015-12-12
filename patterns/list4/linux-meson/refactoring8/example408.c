static struct class_attribute freq_limit_class_attrs[] = {
	__ATTR(limit, S_IRUGO|S_IWUSR|S_IWGRP, freq_limit_show, freq_limit_store),
	__ATTR(check_clock, S_IRUGO|S_IWUSR|S_IWGRP, check_clock_show, check_clock_store),
#ifdef CONFIG_FIX_SYSPLL
	__ATTR(swing_inteval, S_IRUGO|S_IWUSR|S_IWGRP, swing_inteval_show, swing_inteval_store),
#endif
	__ATTR_NULL,
};
