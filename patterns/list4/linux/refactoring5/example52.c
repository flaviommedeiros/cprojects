#ifdef CONFIG_ARCH_LUBBOCK
if (machine_is_lubbock()) {
		retval = devm_request_irq(&pdev->dev, LUBBOCK_USB_DISC_IRQ,
					  lubbock_vbus_irq, 0, driver_name,
					  dev);
		if (retval != 0) {
			pr_err("%s: can't get irq %i, err %d\n",
				driver_name, LUBBOCK_USB_DISC_IRQ, retval);
			goto err;
		}
		retval = devm_request_irq(&pdev->dev, LUBBOCK_USB_IRQ,
					  lubbock_vbus_irq, 0, driver_name,
					  dev);
		if (retval != 0) {
			pr_err("%s: can't get irq %i, err %d\n",
				driver_name, LUBBOCK_USB_IRQ, retval);
			goto err;
		}
	} else
#endif
	create_debug_files(dev);
