#ifdef CONFIG_LEDS_TRIGGERS
if (corgi_amber_led.trigger && strcmp(corgi_amber_led.trigger->name, "sharpsl-charge"))
#endif
		led_classdev_suspend(&corgi_amber_led);
