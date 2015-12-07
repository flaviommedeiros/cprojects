#ifdef CONFIG_LEDS_TRIGGERS
if (tosa_amber_led.trigger && strcmp(tosa_amber_led.trigger->name,
						"sharpsl-charge"))
#endif
		led_classdev_suspend(&tosa_amber_led);
