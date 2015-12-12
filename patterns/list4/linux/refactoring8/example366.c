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
#else
# error no gpio arrays defined
#endif
};
