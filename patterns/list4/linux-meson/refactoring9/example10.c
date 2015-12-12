int pcd_init(
#ifdef LM_INTERFACE
	struct lm_device *_dev
#elif  defined(PCI_INTERFACE)
	struct pci_dev *_dev
#endif
    )
{
#ifdef LM_INTERFACE
	dwc_otg_device_t *otg_dev = lm_get_drvdata(_dev);
#elif  defined(PCI_INTERFACE)
	dwc_otg_device_t *otg_dev = pci_get_drvdata(_dev);
#endif

	int retval = 0;

	DWC_DEBUGPL(DBG_PCDV, "%s(%p)\n", __func__, _dev);

	otg_dev->pcd = dwc_otg_pcd_init(otg_dev->core_if);

	if (!otg_dev->pcd) {
		DWC_ERROR("dwc_otg_pcd_init failed\n");
		return -ENOMEM;
	}

	otg_dev->pcd->otg_dev = otg_dev;
	gadget_wrapper = alloc_wrapper(_dev);
	
	/*
	 * Initialize EP structures
	 */
	gadget_add_eps(gadget_wrapper);
	/*
	 * Setup interupt handler
	 */
	DWC_DEBUGPL(DBG_ANY, "registering handler for irq%d\n", _dev->irq);
	retval = request_irq(_dev->irq, dwc_otg_pcd_irq,
			     IRQF_SHARED | IRQF_DISABLED,
			     gadget_wrapper->gadget.name, otg_dev->pcd);
	if (retval != 0) {
		DWC_ERROR("request of irq%d failed\n", _dev->irq);
		free_wrapper(gadget_wrapper);
		return -EBUSY;
	}

	dwc_otg_pcd_start(gadget_wrapper->pcd, &fops);

	return retval;
}
