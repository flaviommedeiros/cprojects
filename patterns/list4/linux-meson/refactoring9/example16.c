static void dwc_otg_driver_remove(
#ifdef LM_INTERFACE
					 struct lm_device *_dev
#elif defined(PCI_INTERFACE)
					 struct pci_dev *_dev
#endif
    )
{
#ifdef LM_INTERFACE
	dwc_otg_device_t *otg_dev = lm_get_drvdata(_dev);
#elif defined(PCI_INTERFACE)
	dwc_otg_device_t *otg_dev = pci_get_drvdata(_dev);
#endif

	DWC_DEBUGPL(DBG_ANY, "%s(%p)\n", __func__, _dev);

	if (!otg_dev) {
		/* Memory allocation for the dwc_otg_device failed. */
		DWC_DEBUGPL(DBG_ANY, "%s: otg_dev NULL!\n", __func__);
		return;
	}
#ifndef DWC_DEVICE_ONLY
	if (otg_dev->hcd) {
		hcd_remove(_dev);
	} else {
		DWC_DEBUGPL(DBG_ANY, "%s: otg_dev->hcd NULL!\n", __func__);
		return;
	}
#endif

#ifndef DWC_HOST_ONLY
	if (otg_dev->pcd) {
		pcd_remove(_dev);
	} else {
		DWC_DEBUGPL(DBG_ANY, "%s: otg_dev->pcd NULL!\n", __func__);
		return;
	}
#endif
	/*
	 * Free the IRQ
	 */
	if (otg_dev->common_irq_installed) {
		free_irq(_dev->irq, otg_dev);
	} else {
		DWC_DEBUGPL(DBG_ANY, "%s: There is no installed irq!\n", __func__);
		return;
	}

	if (otg_dev->core_if) {
		amlogic_gpio_free(otg_dev->core_if->vbus_power_pin,VBUS_POWER_GPIO_OWNER);
		dwc_otg_cil_remove(otg_dev->core_if);
	} else {
		DWC_DEBUGPL(DBG_ANY, "%s: otg_dev->core_if NULL!\n", __func__);
		return;
	}

	if(otg_dev->id_change_timer)
		DWC_TIMER_FREE(otg_dev->id_change_timer);

	/*
	 * Remove the device attributes
	 */
	dwc_otg_attr_remove(_dev);

	/*
	 * Return the memory.
	 */
	if (otg_dev->os_dep.base) {
		iounmap(otg_dev->os_dep.base);
	}
	DWC_FREE(otg_dev);

	/*
	 * Clear the drvdata pointer.
	 */
#ifdef LM_INTERFACE
	lm_set_drvdata(_dev, 0);
#elif defined(PCI_INTERFACE)
    release_mem_region(otg_dev->os_dep.rsrc_start, otg_dev->os_dep.rsrc_len);
	pci_set_drvdata(_dev, 0);
#endif
}
