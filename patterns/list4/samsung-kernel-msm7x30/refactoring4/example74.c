#ifdef WAKE_GPIO_ACTIVE_HIGH
if (!gpio_get_value(bsi->host_wake))
#else
	if (gpio_get_value(bsi->host_wake))
#endif
		bluesleep_rx_busy();
	else
		bluesleep_rx_idle();
