#ifdef CONFIG_PCI_MSI
if (vdev->config.intr_type == MSI_X) {
		vxge_rem_msix_isr(vdev);
	} else
#endif
	if (vdev->config.intr_type == INTA) {
			synchronize_irq(vdev->pdev->irq);
			free_irq(vdev->pdev->irq, vdev);
	}
