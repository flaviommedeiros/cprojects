void hcd_remove(
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

	dwc_otg_hcd_t *dwc_otg_hcd;
	struct usb_hcd *hcd;

	DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD REMOVE\n");

	if (!otg_dev) {
		DWC_DEBUGPL(DBG_ANY, "%s: otg_dev NULL!\n", __func__);
		return;
	}

	dwc_otg_hcd = otg_dev->hcd;

	if (!dwc_otg_hcd) {
		DWC_DEBUGPL(DBG_ANY, "%s: otg_dev->hcd NULL!\n", __func__);
		return;
	}

	hcd = dwc_otg_hcd_to_hcd(dwc_otg_hcd);

	if (!hcd) {
		DWC_DEBUGPL(DBG_ANY,
			    "%s: dwc_otg_hcd_to_hcd(dwc_otg_hcd) NULL!\n",
			    __func__);
		return;
	}
	usb_remove_hcd(hcd);
	dwc_otg_hcd_set_priv_data(dwc_otg_hcd, NULL);
	dwc_otg_hcd_remove(dwc_otg_hcd);
	usb_put_hcd(hcd);
}
