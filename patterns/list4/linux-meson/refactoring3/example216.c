switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		bcma_chipco_gpio_control(&dev->dev->bdev->bus->drv_cc, ~0, 0);
		break;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		gpiodev = b43_ssb_gpio_dev(dev);
		if (gpiodev)
			ssb_write32(gpiodev, B43_GPIO_CONTROL, 0);
		break;
#endif
	}
