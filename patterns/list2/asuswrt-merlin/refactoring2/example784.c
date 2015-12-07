#ifdef CONFIG_X86_LOCAL_APIC
if (notify_die(DIE_NMI, "nmi", regs, reason, 2, SIGINT)
							== NOTIFY_STOP)
			return;
