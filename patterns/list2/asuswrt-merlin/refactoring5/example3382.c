#ifdef CONFIG_ARCH_LUBBOCK
if (machine_is_lubbock()) {
		retval = request_irq(LUBBOCK_USB_DISC_IRQ,
				lubbock_vbus_irq,
				IRQF_DISABLED | IRQF_SAMPLE_RANDOM,
				driver_name, dev);
		if (retval != 0) {
			pr_err("%s: can't get irq %i, err %d\n",
				driver_name, LUBBOCK_USB_DISC_IRQ, retval);
lubbock_fail0:
			goto err_irq_lub;
		}
		retval = request_irq(LUBBOCK_USB_IRQ,
				lubbock_vbus_irq,
				IRQF_DISABLED | IRQF_SAMPLE_RANDOM,
				driver_name, dev);
		if (retval != 0) {
			pr_err("%s: can't get irq %i, err %d\n",
				driver_name, LUBBOCK_USB_IRQ, retval);
			free_irq(LUBBOCK_USB_DISC_IRQ, dev);
			goto lubbock_fail0;
		}
	} else
#endif
	if (vbus_irq) {
		retval = request_irq(vbus_irq, udc_vbus_irq,
				IRQF_DISABLED | IRQF_SAMPLE_RANDOM |
				IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
				driver_name, dev);
		if (retval != 0) {
			pr_err("%s: can't get irq %i, err %d\n",
				driver_name, vbus_irq, retval);
			goto err_vbus_irq;
		}
	}
