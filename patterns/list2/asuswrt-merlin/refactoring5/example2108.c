#ifdef CONFIG_COMPAT
if (compat) {
		num_counters = compat_tmp.num_counters;
		name = compat_tmp.name;
	} else
#endif
	{
		num_counters = tmp.num_counters;
		name = tmp.name;
	}
