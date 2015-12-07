#ifdef CONFIG_X86_LOCAL_APIC
if (nmi_watchdog_tick(regs, reason))
			return;
