switch (adapter->intr.type) {
#ifdef CONFIG_PCI_MSI
	case VMXNET3_IT_MSIX: {
		int i;
		for (i = 0; i < adapter->num_rx_queues; i++)
			vmxnet3_msix_rx(0, &adapter->rx_queue[i]);
		break;
	}
#endif
	case VMXNET3_IT_MSI:
	default:
		vmxnet3_intr(0, adapter->netdev);
		break;
	}
