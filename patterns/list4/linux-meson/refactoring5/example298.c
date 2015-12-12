#ifdef CONFIG_COMPAT
if (is_compat_task()) {
			if (addr & (sizeof(compat_long_t)-1))
				break;
			*(compat_long_t *)childreg = data;
		} else
#endif
		{
			if (addr & (sizeof(long)-1))
				break;
			*(long *)childreg = data;
		}
