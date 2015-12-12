switch(sig) {
		case SIGSEGV:
#ifndef _WIN32
		case SIGBUS:
#endif
		case SIGILL:
		case SIGABRT:
		case SIGFPE: {
#if !defined(_WIN32) && !defined(__mips__)
			log_shell_disable();
			void *stack[50];
			int n = backtrace(stack, 50);
			printf("-- STACKTRACE (%d FRAMES) --\n", n);
			logerror("-- STACKTRACE (%d FRAMES) --", n);

			unw_getcontext(&uc);
			unw_init_local(&cursor, &uc);

			while(unw_step(&cursor) > 0) {
				name[0] = '\0';
				unw_get_proc_name(&cursor, name, 256, &offp);
				unw_get_reg(&cursor, UNW_REG_IP, &ip);
				unw_get_reg(&cursor, UNW_REG_SP, &sp);

				printf("%-30s ip = %10p, sp = %10p\n", name, (void *)ip, (void *)sp);
				logerror("%-30s ip = %10p, sp = %10p", name, (void *)ip, (void *)sp);
			}
#endif
		}
		break;
		default:;
	}
