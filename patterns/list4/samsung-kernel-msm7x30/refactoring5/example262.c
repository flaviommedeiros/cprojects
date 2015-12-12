#ifdef CONFIG_COMPAT
if (is_compat_task()) {
			if (addr & (sizeof(compat_long_t)-1))
				break;
			ret = put_user(*(compat_long_t *)childreg,
				       (compat_long_t __user *)datap);
		} else
#endif
		{
			if (addr & (sizeof(long)-1))
				break;
			ret = put_user(*(long *)childreg, datap);
		}
