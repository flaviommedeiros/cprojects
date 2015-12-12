switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		bcma_core_pci_irq_ctl(&dev->dev->bdev->bus->drv_pci[0],
				      dev->dev->bdev, true);
		break;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		ssb_pcicore_dev_irqvecs_enable(&dev->dev->sdev->bus->pcicore,
					       dev->dev->sdev);
		break;
#endif
	}
