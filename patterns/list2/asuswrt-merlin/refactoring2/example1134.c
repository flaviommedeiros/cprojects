#ifdef CONFIG_LEDS_TRIGGERS
if (spitz_amber_led.trigger && strcmp(spitz_amber_led.trigger->name, "sharpsl-charge"))
#endif
		led_classdev_suspend(&spitz_amber_led);
