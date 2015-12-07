#ifdef BF537_GENERIC_ERROR_INT_DEMUX
if (irq != IRQ_GENERIC_ERROR) {
#endif

#ifdef CONFIG_IRQCHIP_DEMUX_GPIO
			if ((irq != IRQ_PROG_INTA) /*PORT F & G MASK_A Interrupt*/
# if defined(BF537_FAMILY) && !(defined(CONFIG_BFIN_MAC) || defined(CONFIG_BFIN_MAC_MODULE))
				&& (irq != IRQ_MAC_RX) /*PORT H MASK_A Interrupt*/
# endif
			    ) {
#endif
				set_irq_handler(irq, handle_simple_irq);
#ifdef CONFIG_IRQCHIP_DEMUX_GPIO
			} else {
				set_irq_chained_handler(irq,
							bfin_demux_gpio_irq);
			}
#endif

#ifdef BF537_GENERIC_ERROR_INT_DEMUX
		} else {
			set_irq_handler(irq, bfin_demux_error_irq);
		}
