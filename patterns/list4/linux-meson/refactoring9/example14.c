int hcd_init(
#ifdef LM_INTERFACE
		    struct lm_device *_dev
#elif  defined(PCI_INTERFACE)
		    struct pci_dev *_dev
#endif
    )
{
	struct usb_hcd *hcd = NULL;
	dwc_otg_hcd_t *dwc_otg_hcd = NULL;
#ifdef LM_INTERFACE
	dwc_otg_device_t *otg_dev = lm_get_drvdata(_dev);
#elif  defined(PCI_INTERFACE)
	dwc_otg_device_t *otg_dev = pci_get_drvdata(_dev);
#endif

	int retval = 0;

	DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD INIT\n");
	
#if 0 /* move to dwc_otg_driver_probe*/
	/* Set device flags indicating whether the HCD supports DMA. */
	if (dwc_otg_is_dma_enable(otg_dev->core_if)) {
#ifdef LM_INTERFACE
		_dev->dev.dma_mask = (void *)~0;
		_dev->dev.coherent_dma_mask = ~0;
#elif  defined(PCI_INTERFACE)
		pci_set_dma_mask(_dev, DMA_32BIT_MASK);
		pci_set_consistent_dma_mask(_dev, DMA_32BIT_MASK);
#endif

	} else {
#ifdef LM_INTERFACE
		_dev->dev.dma_mask = (void *)0;
		_dev->dev.coherent_dma_mask = 0;
#elif  defined(PCI_INTERFACE)
		pci_set_dma_mask(_dev, 0);
		pci_set_consistent_dma_mask(_dev, 0);
#endif
	}
#endif
	/*
	 * Allocate memory for the base HCD plus the DWC OTG HCD.
	 * Initialize the base HCD.
	 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,30)
	hcd = usb_create_hcd(&dwc_otg_hc_driver, &_dev->dev, _dev->dev.bus_id);
#else
	hcd = usb_create_hcd(&dwc_otg_hc_driver, &_dev->dev, dev_name(&_dev->dev));
	hcd->has_tt = 1;
//      hcd->uses_new_polling = 1;
//      hcd->poll_rh = 0;
#endif
	if (!hcd) {
		retval = -ENOMEM;
		goto error1;
	}

	hcd->regs = otg_dev->os_dep.base;

	/* Initialize the DWC OTG HCD. */
	dwc_otg_hcd = dwc_otg_hcd_alloc_hcd();
	if (!dwc_otg_hcd) {
		goto error2;
	}
	((struct wrapper_priv_data *)(hcd->hcd_priv))->dwc_otg_hcd =
	    dwc_otg_hcd;
	otg_dev->hcd = dwc_otg_hcd;

	if (dwc_otg_hcd_init(dwc_otg_hcd, otg_dev->core_if)) {
		goto error2;
	}

	otg_dev->hcd->otg_dev = otg_dev;
	hcd->self.otg_port = dwc_otg_hcd_otg_port(dwc_otg_hcd);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,33) //don't support for LM(with 2.6.20.1 kernel)
//	hcd->self.otg_version = dwc_otg_get_otg_version(otg_dev->core_if);
	/* Don't support SG list at this point */
	hcd->self.sg_tablesize = 0;
#endif
	/*
	 * Finish generic HCD initialization and start the HCD. This function
	 * allocates the DMA buffer pool, registers the USB bus, requests the
	 * IRQ line, and calls hcd_start method.
	 */
	retval = usb_add_hcd(hcd, _dev->irq, IRQF_SHARED | IRQF_DISABLED);
	if (retval < 0) {
		goto error2;
	}

	dwc_otg_hcd_set_priv_data(dwc_otg_hcd, hcd);
	return 0;

error2:
	usb_put_hcd(hcd);
error1:
	return retval;
}
