switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
		case B43_BUS_BCMA:
			bcma_chipco_gpio_control(&dev->dev->bdev->bus->drv_cc,
						 0xFC00, 0xFC00);
			break;
#endif
#ifdef CONFIG_B43_SSB
		case B43_BUS_SSB:
			ssb_chipco_gpio_control(&dev->dev->sdev->bus->chipco,
						0xFC00, 0xFC00);
			break;
#endif
		}
