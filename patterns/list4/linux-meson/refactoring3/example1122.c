switch (ipinr) {
	case IPI_WAKEUP:
		break;

#ifdef CONFIG_GENERIC_CLOCKEVENTS_BROADCAST
	case IPI_TIMER:
		irq_enter();
		tick_receive_broadcast();
		irq_exit();
		break;
#endif

	case IPI_RESCHEDULE:
		scheduler_ipi();
		break;

	case IPI_CALL_FUNC:
		irq_enter();
		generic_smp_call_function_interrupt();
		irq_exit();
		break;

	case IPI_CALL_FUNC_SINGLE:
		irq_enter();
		generic_smp_call_function_single_interrupt();
		irq_exit();
		break;

	case IPI_CPU_STOP:
		irq_enter();
		ipi_cpu_stop(cpu);
		irq_exit();
		break;

	case IPI_CPU_BACKTRACE:
		ipi_cpu_backtrace(cpu, regs);
		break;

	default:
		printk(KERN_CRIT "CPU%u: Unknown IPI message 0x%x\n",
		       cpu, ipinr);
		break;
	}
