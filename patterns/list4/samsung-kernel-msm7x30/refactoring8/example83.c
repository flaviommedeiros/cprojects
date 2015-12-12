static struct device_attribute led_class_attrs[] = {
	__ATTR(brightness, 0644, led_brightness_show, led_brightness_store),
	__ATTR(max_brightness, 0644, led_max_brightness_show,
			led_max_brightness_store),
#ifdef CONFIG_LEDS_TRIGGERS
	__ATTR(trigger, 0644, led_trigger_show, led_trigger_store),
#endif
	__ATTR_NULL,
};
