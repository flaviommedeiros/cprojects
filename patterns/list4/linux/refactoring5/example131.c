#ifdef CONFIG_SUN_LDOMS
if (ldom_domaining_enabled) {
				unsigned long hv_err;
				hv_err = sun4v_cpu_stop(cpu);
				if (hv_err)
					printk(KERN_ERR "sun4v_cpu_stop() "
					       "failed err=%lu\n", hv_err);
			} else
#endif
				prom_stopcpu_cpuid(cpu);
