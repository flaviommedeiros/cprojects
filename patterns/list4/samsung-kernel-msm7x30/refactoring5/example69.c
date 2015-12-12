#ifdef CONFIG_ARCH_LUBBOCK
if (machine_is_lubbock()) {
		retval = request_irq(LUBBOCK_USB_DISC_IRQ,
				lubbock_vbus_irq,
				IRQF_SAMPLE_RANDOM,
				driver_name, dev);
		if (retval != 0) {
			pr_err("%s: can't get irq %i, err %d\n",
				driver_name, LUBBOCK_USB_DISC_IRQ, retval);
			goto err_irq_lub;
		}
		retval = request_irq(LUBBOCK_USB_IRQ,
				lubbock_vbus_irq,
				IRQF_SAMPLE_RANDOM,
				driver_name, dev);
		if (retval != 0) {
			pr_err("%s: can't get irq %i, err %d\n",
				driver_name, LUBBOCK_USB_IRQ, retval);
			goto lubbock_fail0;
		}
	} else
#endif
	create_debug_files(dev);
