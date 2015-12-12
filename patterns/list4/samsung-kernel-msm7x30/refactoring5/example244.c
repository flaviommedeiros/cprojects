#ifdef CONFIG_SPARC_LEON
if (pm_idle) {
			while (!need_resched())
				(*pm_idle)();
		} else
#endif
		{
			while (!need_resched())
				cpu_relax();
		}
