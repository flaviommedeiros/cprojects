switch(evt) {
	case led_start:		/* System startup */
		at91_led_on(at91_leds_cpu);
		break;

	case led_stop:		/* System stop / suspend */
		at91_led_off(at91_leds_cpu);
		break;

#ifdef CONFIG_LEDS_TIMER
	case led_timer:		/* Every 50 timer ticks */
		at91_led_toggle(at91_leds_timer);
		break;
#endif

#ifdef CONFIG_LEDS_CPU
	case led_idle_start:	/* Entering idle state */
		at91_led_off(at91_leds_cpu);
		break;

	case led_idle_end:	/* Exit idle state */
		at91_led_on(at91_leds_cpu);
		break;
#endif

	default:
		break;
	}
