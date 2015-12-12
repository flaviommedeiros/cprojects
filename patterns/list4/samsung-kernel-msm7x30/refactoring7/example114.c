return (state == PM_SUSPEND_STANDBY
#if !(defined(BF533_FAMILY) || defined(CONFIG_BF561))
	/*
	 * On BF533/2/1:
	 * If we enter Hibernate the SCKE Pin is driven Low,
	 * so that the SDRAM enters Self Refresh Mode.
	 * However when the reset sequence that follows hibernate
	 * state is executed, SCKE is driven High, taking the
	 * SDRAM out of Self Refresh.
	 *
	 * If you reconfigure and access the SDRAM "very quickly",
	 * you are likely to avoid errors, otherwise the SDRAM
	 * start losing its contents.
	 * An external HW workaround is possible using logic gates.
	 */
	|| state == PM_SUSPEND_MEM
#endif
	);
