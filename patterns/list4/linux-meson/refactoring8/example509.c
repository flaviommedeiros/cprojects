static struct gpio_port_t * const gpio_array[] = {
#if defined(BF533_FAMILY) || defined(BF538_FAMILY)
	(struct gpio_port_t *) FIO_FLAG_D,
#elif defined(CONFIG_BF52x) || defined(BF537_FAMILY) || defined(CONFIG_BF51x)
	(struct gpio_port_t *) PORTFIO,
	(struct gpio_port_t *) PORTGIO,
	(struct gpio_port_t *) PORTHIO,
#elif defined(BF561_FAMILY)
	(struct gpio_port_t *) FIO0_FLAG_D,
	(struct gpio_port_t *) FIO1_FLAG_D,
	(struct gpio_port_t *) FIO2_FLAG_D,
#elif defined(CONFIG_BF54x) || defined(CONFIG_BF60x) 
	(struct gpio_port_t *)PORTA_FER,
	(struct gpio_port_t *)PORTB_FER,
	(struct gpio_port_t *)PORTC_FER,
	(struct gpio_port_t *)PORTD_FER,
	(struct gpio_port_t *)PORTE_FER,
	(struct gpio_port_t *)PORTF_FER,
	(struct gpio_port_t *)PORTG_FER,
# if defined(CONFIG_BF54x)
	(struct gpio_port_t *)PORTH_FER,
	(struct gpio_port_t *)PORTI_FER,
	(struct gpio_port_t *)PORTJ_FER,
# endif
#else
# error no gpio arrays defined
#endif
};
