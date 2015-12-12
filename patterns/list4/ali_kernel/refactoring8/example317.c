struct gpio_chip alchemy_gpio_chip[] = {
	[0] = {
		.label			= "alchemy-gpio1",
		.direction_input	= gpio1_direction_input,
		.direction_output	= gpio1_direction_output,
		.get			= gpio1_get,
		.set			= gpio1_set,
		.to_irq			= gpio1_to_irq,
		.base			= ALCHEMY_GPIO1_BASE,
		.ngpio			= ALCHEMY_GPIO1_NUM,
	},
#if !defined(CONFIG_SOC_AU1000)
	[1] = {
		.label                  = "alchemy-gpio2",
		.direction_input        = gpio2_direction_input,
		.direction_output       = gpio2_direction_output,
		.get                    = gpio2_get,
		.set                    = gpio2_set,
		.to_irq			= gpio2_to_irq,
		.base                   = ALCHEMY_GPIO2_BASE,
		.ngpio                  = ALCHEMY_GPIO2_NUM,
	},
#endif
};
