switch(evt) {
	case led_start:		/* System startup */
		ks8695_led_on(ks8695_leds_cpu);
		break;

	case led_stop:		/* System stop / suspend */
		ks8695_led_off(ks8695_leds_cpu);
		break;

#ifdef CONFIG_LEDS_TIMER
	case led_timer:		/* Every 50 timer ticks */
		ks8695_led_toggle(ks8695_leds_timer);
		break;
#endif

#ifdef CONFIG_LEDS_CPU
	case led_idle_start:	/* Entering idle state */
		ks8695_led_off(ks8695_leds_cpu);
		break;

	case led_idle_end:	/* Exit idle state */
		ks8695_led_on(ks8695_leds_cpu);
		break;
#endif

	default:
		break;
	}
