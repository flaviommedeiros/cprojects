void pcd_remove(
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
	dwc_otg_pcd_t *pcd = otg_dev->pcd;

	DWC_DEBUGPL(DBG_PCDV, "%s(%p)\n", __func__, _dev);

	/*
	 * Free the IRQ
	 */
	free_irq(_dev->irq, pcd);
	free_wrapper(gadget_wrapper);
	dwc_otg_pcd_remove(otg_dev->pcd);	
	otg_dev->pcd = 0;
}
