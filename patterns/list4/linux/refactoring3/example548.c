switch (irq) {
	case TIMER0_IRQ:
#ifdef CONFIG_SMP
	case IPI_IRQ:
#endif
		irq_set_chip_and_handler(irq, &onchip_intc, handle_percpu_irq);
		break;
	default:
		irq_set_chip_and_handler(irq, &onchip_intc, handle_level_irq);
	}
