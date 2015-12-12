#ifdef CONFIG_MODULES
if (!ss)
#endif
		{
			rcu_read_unlock();
			return -EINVAL;
		}
