switch (skt->nr) {
	case 0:
		if (gpio_request(GPIO_PRDY, "cf_irq") < 0) {
			pr_err("%s: sock %d unable to request gpio %d\n", __func__,
				skt->nr, GPIO_PRDY);
			return -EBUSY;
		}
		if (gpio_direction_input(GPIO_PRDY) < 0) {
			pr_err("%s: sock %d unable to set input gpio %d\n", __func__,
				skt->nr, GPIO_PRDY);
			gpio_free(GPIO_PRDY);
			return -EINVAL;
		}
		skt->irq = IRQ_GPIO(GPIO_PRDY);
		break;

#ifndef CONFIG_MACH_TRIZEPS_CONXS
	case 1:
#endif
	default:
		break;
	}
