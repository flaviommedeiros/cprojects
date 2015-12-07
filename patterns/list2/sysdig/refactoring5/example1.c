#ifdef _HAS_SOCKETCALL
if (args->is_socketcall && evinfo->paramtype == APT_SOCK) {
				val = args->socketcall_args[evinfo->autofill_args[j].id];
			} else
#endif
			{
				/*
				 * Regular argument
				 */
				syscall_get_arguments(current,
						args->regs,
						evinfo->autofill_args[j].id,
						1,
						&val);
			}
