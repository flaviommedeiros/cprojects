if ((hw->wiphy->wowlan.flags || hw->wiphy->wowlan.n_patterns)
#ifdef CONFIG_PM
	    && (!local->ops->suspend || !local->ops->resume)
#endif
	    )
		return -EINVAL;
