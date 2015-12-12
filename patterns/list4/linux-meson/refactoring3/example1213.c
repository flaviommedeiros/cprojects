switch (ext) {
	case KVM_CAP_IRQCHIP:
	case KVM_CAP_MP_STATE:
	case KVM_CAP_IRQ_INJECT_STATUS:
		r = 1;
		break;
	case KVM_CAP_COALESCED_MMIO:
		r = KVM_COALESCED_MMIO_PAGE_OFFSET;
		break;
#ifdef CONFIG_KVM_DEVICE_ASSIGNMENT
	case KVM_CAP_IOMMU:
		r = iommu_present(&pci_bus_type);
		break;
#endif
	default:
		r = 0;
	}
