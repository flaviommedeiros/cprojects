#ifdef CONFIG_PCI_MSI
if (adapter->intr.type == VMXNET3_IT_MSIX) {
		/* we only use 1 MSI-X vector */
		err = request_irq(adapter->intr.msix_entries[0].vector,
				  vmxnet3_intr, 0, adapter->netdev->name,
				  adapter->netdev);
	} else if (adapter->intr.type == VMXNET3_IT_MSI) {
		err = request_irq(adapter->pdev->irq, vmxnet3_intr, 0,
				  adapter->netdev->name, adapter->netdev);
	} else
#endif
	{
		err = request_irq(adapter->pdev->irq, vmxnet3_intr,
				  IRQF_SHARED, adapter->netdev->name,
				  adapter->netdev);
	}
