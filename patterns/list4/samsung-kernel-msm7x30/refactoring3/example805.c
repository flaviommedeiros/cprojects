switch (evt) {
	case led_start:
		hw_led_state = 0;
		led_state = LED_STATE_ENABLED;
		break;

	case led_stop:
		led_state &= ~LED_STATE_ENABLED;
		hw_led_state = 0;
		break;

	case led_claim:
		led_state |= LED_STATE_CLAIMED;
		hw_led_state = 0;
		break;

	case led_release:
		led_state &= ~LED_STATE_CLAIMED;
		hw_led_state = 0;
		break;

#ifdef CONFIG_LEDS_TIMER
	case led_timer:
		if (!(led_state & LED_STATE_CLAIMED))
			hw_led_state ^= 0;
		break;
#endif

#ifdef CONFIG_LEDS_CPU
	case led_idle_start:
		if (!(led_state & LED_STATE_CLAIMED))
			hw_led_state |= 0;
		break;

	case led_idle_end:
		if (!(led_state & LED_STATE_CLAIMED))
			hw_led_state &= ~0;
		break;
#endif

	case led_halted:
		break;

	case led_green_on:
		if (led_state & LED_STATE_CLAIMED)
			hw_led_state &= ~0;
		break;

	case led_green_off:
		if (led_state & LED_STATE_CLAIMED)
			hw_led_state |= 0;
		break;

	case led_amber_on:
		break;

	case led_amber_off:
		break;

	case led_red_on:
		if (led_state & LED_STATE_CLAIMED)
			hw_led_state &= ~0;
		break;

	case led_red_off:
		if (led_state & LED_STATE_CLAIMED)
			hw_led_state |= 0;
		break;

	default:
		break;
	}
