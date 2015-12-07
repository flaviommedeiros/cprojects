#ifdef CONFIG_X86_PM_TIMER
if (apic_calibrate_pmtmr && pmtmr_ioport) {
		pmtimer_wait(5000);  /* 5ms wait */
		apic = apic_read(APIC_TMCCT);
		result = (apic_start - apic) * 1000L / 5;
	} else
#endif
	{
		rdtscll(tsc_start);

		do {
			apic = apic_read(APIC_TMCCT);
			rdtscll(tsc);
		} while ((tsc - tsc_start) < TICK_COUNT &&
				(apic_start - apic) < TICK_COUNT);

		result = (apic_start - apic) * 1000L * tsc_khz /
					(tsc - tsc_start);
	}
