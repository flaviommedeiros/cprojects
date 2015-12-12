switch(evt) {
	case led_start:
		/* pin 23 is output pin */
		GPDR |= LED_23;
		hw_led_state = LED_MASK;
		led_state = LED_STATE_ENABLED;
		break;

	case led_stop:
		led_state &= ~LED_STATE_ENABLED;
		break;

	case led_claim:
		led_state |= LED_STATE_CLAIMED;
		hw_led_state = LED_MASK;
		break;

	case led_release:
		led_state &= ~LED_STATE_CLAIMED;
		hw_led_state = LED_MASK;
		break;

#ifdef CONFIG_LEDS_TIMER
	case led_timer:
		if (!(led_state & LED_STATE_CLAIMED))
			hw_led_state ^= LED_23;
		break;
#endif

#ifdef CONFIG_LEDS_CPU
	case led_idle_start:
		/* The LART people like the LED to be off when the
                   system is idle... */
		if (!(led_state & LED_STATE_CLAIMED))
			hw_led_state &= ~LED_23;
		break;

	case led_idle_end:
		/* ... and on if the system is not idle */
		if (!(led_state & LED_STATE_CLAIMED))
			hw_led_state |= LED_23;
		break;
#endif

	case led_red_on:
		if (led_state & LED_STATE_CLAIMED)
			hw_led_state &= ~LED_23;
		break;

	case led_red_off:
		if (led_state & LED_STATE_CLAIMED)
			hw_led_state |= LED_23;
		break;

	default:
		break;
	}
