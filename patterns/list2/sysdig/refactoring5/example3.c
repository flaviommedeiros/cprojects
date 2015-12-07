#ifdef CONFIG_COMPAT
if (unlikely(args->compat))
				env_len = compat_accumulate_argv_or_env( (compat_uptr_t)val,
							  args->str_storage, available);
			else
#endif
				env_len = accumulate_argv_or_env((const char __user * __user *)val,
							  args->str_storage, available);
