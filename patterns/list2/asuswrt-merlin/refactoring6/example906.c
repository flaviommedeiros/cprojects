if (machine_is_omap_h2()
			|| machine_is_omap_h3()
#ifdef	CONFIG_OMAP_OSK_MISTRAL
			|| machine_is_omap_osk()
#endif
			) {

		/* LED1/LED2 pins can be used as GPIO (as done here), or by
		 * the LPG (works even in deep sleep!), to drive a bicolor
		 * LED on the H2 sample board, and another on the H2/P2
		 * "surfer" expansion board.
		 *
		 * The same pins drive a LED on the OSK Mistral board, but
		 * that's a different kind of LED (just one color at a time).
		 */
		omap_cfg_reg(P18_1610_GPIO3);
		if (gpio_request(3, "LED red") == 0)
			gpio_direction_output(3, 1);
		else
			printk(KERN_WARNING "LED: can't get GPIO3/red?\n");

		omap_cfg_reg(MPUIO4);
		if (gpio_request(OMAP_MPUIO(4), "LED green") == 0)
			gpio_direction_output(OMAP_MPUIO(4), 1);
		else
			printk(KERN_WARNING "LED: can't get MPUIO4/green?\n");
	}
