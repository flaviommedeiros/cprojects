#ifdef CONFIG_PCI_MSI
if (adapter->intr.type == VMXNET3_IT_MSIX)
		irq = adapter->intr.msix_entries[0].vector;
	else
#endif
		irq = adapter->pdev->irq;
