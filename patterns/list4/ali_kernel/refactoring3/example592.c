switch (irq) {
#if defined(CONFIG_BF53x)
		case IRQ_PROG_INTA:
# if defined(BF537_FAMILY) && !(defined(CONFIG_BFIN_MAC) || defined(CONFIG_BFIN_MAC_MODULE))
		case IRQ_MAC_RX:
# endif
#elif defined(CONFIG_BF54x)
		case IRQ_PINT0:
		case IRQ_PINT1:
		case IRQ_PINT2:
		case IRQ_PINT3:
#elif defined(CONFIG_BF52x) || defined(CONFIG_BF51x)
		case IRQ_PORTF_INTA:
		case IRQ_PORTG_INTA:
		case IRQ_PORTH_INTA:
#elif defined(CONFIG_BF561)
		case IRQ_PROG0_INTA:
		case IRQ_PROG1_INTA:
		case IRQ_PROG2_INTA:
#elif defined(CONFIG_BF538) || defined(CONFIG_BF539)
		case IRQ_PORTF_INTA:
#endif

			set_irq_chained_handler(irq,
						bfin_demux_gpio_irq);
			break;
#ifdef BF537_GENERIC_ERROR_INT_DEMUX
		case IRQ_GENERIC_ERROR:
			set_irq_chained_handler(irq, bfin_demux_error_irq);
			break;
#endif

#ifdef CONFIG_SMP
#ifdef CONFIG_TICKSOURCE_GPTMR0
		case IRQ_TIMER0:
#endif
#ifdef CONFIG_TICKSOURCE_CORETMR
		case IRQ_CORETMR:
#endif
		case IRQ_SUPPLE_0:
		case IRQ_SUPPLE_1:
			set_irq_handler(irq, handle_percpu_irq);
			break;
#endif

#ifdef CONFIG_IPIPE
#ifndef CONFIG_TICKSOURCE_CORETMR
		case IRQ_TIMER0:
			set_irq_handler(irq, handle_simple_irq);
			break;
#endif
		case IRQ_CORETMR:
			set_irq_handler(irq, handle_simple_irq);
			break;
		default:
			set_irq_handler(irq, handle_level_irq);
			break;
#else /* !CONFIG_IPIPE */
		default:
			set_irq_handler(irq, handle_simple_irq);
			break;
#endif /* !CONFIG_IPIPE */
		}
