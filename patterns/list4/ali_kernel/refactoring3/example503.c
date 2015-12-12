switch (evt) {
	case led_start:
		led_state |= LED_STATE_ENABLED;
		hw_led_state = 0;
		leds = ~0;
		break;

	case led_halted:
	case led_stop:
		led_state &= ~LED_STATE_ENABLED;
		hw_led_state = 0;
		break;

	case led_claim:
		led_state |= LED_STATE_CLAIMED;
		hw_led_state = 0;
		leds = ~0;
		break;

	case led_release:
		led_state &= ~LED_STATE_CLAIMED;
		hw_led_state = 0;
		break;

#ifdef	CONFIG_OMAP_OSK_MISTRAL

	case led_timer:
		hw_led_state ^= TIMER_LED;
		mistral_setled();
		break;

	case led_idle_start:	/* idle == off */
		hw_led_state &= ~IDLE_LED;
		mistral_setled();
		break;

	case led_idle_end:
		hw_led_state |= IDLE_LED;
		mistral_setled();
		break;

#endif	/* CONFIG_OMAP_OSK_MISTRAL */

	default:
		break;
	}
