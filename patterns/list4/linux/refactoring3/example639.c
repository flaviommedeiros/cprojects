switch (irq) {
#if !BFIN_GPIO_PINT
#if defined(BF537_FAMILY)
		case IRQ_PH_INTA_MAC_RX:
		case IRQ_PF_INTA_PG_INTA:
#elif defined(BF533_FAMILY)
		case IRQ_PROG_INTA:
#elif defined(CONFIG_BF52x) || defined(CONFIG_BF51x)
		case IRQ_PORTF_INTA:
		case IRQ_PORTG_INTA:
		case IRQ_PORTH_INTA:
#elif defined(CONFIG_BF561)
		case IRQ_PROG0_INTA:
		case IRQ_PROG1_INTA:
		case IRQ_PROG2_INTA:
#elif defined(BF538_FAMILY)
		case IRQ_PORTF_INTA:
#endif
			irq_set_chained_handler(irq, bfin_demux_gpio_irq);
			break;
#endif
#if defined(CONFIG_BFIN_MAC) || defined(CONFIG_BFIN_MAC_MODULE)
		case IRQ_MAC_ERROR:
			irq_set_chained_handler(irq,
						bfin_demux_mac_status_irq);
			break;
#endif
#if defined(CONFIG_SMP) || defined(CONFIG_ICC)
		case IRQ_SUPPLE_0:
		case IRQ_SUPPLE_1:
			irq_set_handler(irq, handle_percpu_irq);
			break;
#endif

#ifdef CONFIG_TICKSOURCE_CORETMR
		case IRQ_CORETMR:
# ifdef CONFIG_SMP
			irq_set_handler(irq, handle_percpu_irq);
# else
			irq_set_handler(irq, handle_simple_irq);
# endif
			break;
#endif

#ifdef CONFIG_TICKSOURCE_GPTMR0
		case IRQ_TIMER0:
			irq_set_handler(irq, handle_simple_irq);
			break;
#endif

		default:
#ifdef CONFIG_IPIPE
			irq_set_handler(irq, handle_level_irq);
#else
			irq_set_handler(irq, handle_simple_irq);
#endif
			break;
		}
