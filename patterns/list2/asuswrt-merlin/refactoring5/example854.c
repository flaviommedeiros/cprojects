#ifdef CONFIG_ARCH_LUBBOCK
if (machine_is_lubbock()) {
		retval = request_irq(LUBBOCK_USB_DISC_IRQ,
				lubbock_vbus_irq,
				IRQF_DISABLED | IRQF_SAMPLE_RANDOM,
				driver_name, dev);
		if (retval != 0) {
			printk(KERN_ERR "%s: can't get irq %i, err %d\n",
				driver_name, LUBBOCK_USB_DISC_IRQ, retval);
lubbock_fail0:
			free_irq(irq, dev);
			if (dev->mach->gpio_pullup)
				gpio_free(dev->mach->gpio_pullup);
			if (dev->mach->gpio_vbus)
				gpio_free(dev->mach->gpio_vbus);
			return -EBUSY;
		}
		retval = request_irq(LUBBOCK_USB_IRQ,
				lubbock_vbus_irq,
				IRQF_DISABLED | IRQF_SAMPLE_RANDOM,
				driver_name, dev);
		if (retval != 0) {
			printk(KERN_ERR "%s: can't get irq %i, err %d\n",
				driver_name, LUBBOCK_USB_IRQ, retval);
			free_irq(LUBBOCK_USB_DISC_IRQ, dev);
			goto lubbock_fail0;
		}
	} else
#endif
	if (vbus_irq) {
		retval = request_irq(vbus_irq, udc_vbus_irq,
				IRQF_DISABLED | IRQF_SAMPLE_RANDOM,
				driver_name, dev);
		if (retval != 0) {
			printk(KERN_ERR "%s: can't get irq %i, err %d\n",
				driver_name, vbus_irq, retval);
			free_irq(irq, dev);
			if (dev->mach->gpio_pullup)
				gpio_free(dev->mach->gpio_pullup);
			if (dev->mach->gpio_vbus)
				gpio_free(dev->mach->gpio_vbus);
			return -EBUSY;
		}
	}
