switch (type_copy) {
	case SMTC_CLOCK_TICK:
		smtc_clock_tick_interrupt();
		break;

	case LINUX_SMP_IPI:
		switch ((int)arg_copy) {
		case SMP_RESCHEDULE_YOURSELF:
			ipi_resched_interrupt();
			break;
		case SMP_CALL_FUNCTION:
			ipi_call_interrupt();
			break;
		default:
			printk("Impossible SMTC IPI Argument %p\n", arg_copy);
			break;
		}
		break;
#ifdef CONFIG_MIPS_MT_SMTC_IRQAFF
	case IRQ_AFFINITY_IPI:
		/*
		 * Accept a "forwarded" interrupt that was initially
		 * taken by a TC who doesn't have affinity for the IRQ.
		 */
		do_IRQ_no_affinity((int)arg_copy);
		break;
#endif /* CONFIG_MIPS_MT_SMTC_IRQAFF */
	default:
		printk("Impossible SMTC IPI Type 0x%x\n", type_copy);
		break;
	}
