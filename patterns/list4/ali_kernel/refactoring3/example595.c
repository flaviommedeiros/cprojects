switch (which) {
			case IPI_CPU_STOP:
				stop_this_cpu();
				break;
			case IPI_CALL_FUNC:
				generic_smp_call_function_interrupt();
				break;
			case IPI_CALL_FUNC_SINGLE:
				generic_smp_call_function_single_interrupt();
				break;
#ifdef CONFIG_KEXEC
			case IPI_KDUMP_CPU_STOP:
				unw_init_running(kdump_cpu_freeze, NULL);
				break;
#endif
			default:
				printk(KERN_CRIT "Unknown IPI on CPU %d: %lu\n",
						this_cpu, which);
				break;
			}
