switch (ext) {
	case KVM_CAP_IRQCHIP:
	case KVM_CAP_HLT:
	case KVM_CAP_MMU_SHADOW_CACHE_CONTROL:
	case KVM_CAP_SET_TSS_ADDR:
	case KVM_CAP_EXT_CPUID:
	case KVM_CAP_CLOCKSOURCE:
	case KVM_CAP_PIT:
	case KVM_CAP_NOP_IO_DELAY:
	case KVM_CAP_MP_STATE:
	case KVM_CAP_SYNC_MMU:
	case KVM_CAP_USER_NMI:
	case KVM_CAP_REINJECT_CONTROL:
	case KVM_CAP_IRQ_INJECT_STATUS:
	case KVM_CAP_IRQFD:
	case KVM_CAP_IOEVENTFD:
	case KVM_CAP_PIT2:
	case KVM_CAP_PIT_STATE2:
	case KVM_CAP_SET_IDENTITY_MAP_ADDR:
	case KVM_CAP_XEN_HVM:
	case KVM_CAP_ADJUST_CLOCK:
	case KVM_CAP_VCPU_EVENTS:
	case KVM_CAP_HYPERV:
	case KVM_CAP_HYPERV_VAPIC:
	case KVM_CAP_HYPERV_SPIN:
	case KVM_CAP_PCI_SEGMENT:
	case KVM_CAP_DEBUGREGS:
	case KVM_CAP_X86_ROBUST_SINGLESTEP:
	case KVM_CAP_XSAVE:
	case KVM_CAP_ASYNC_PF:
	case KVM_CAP_GET_TSC_KHZ:
	case KVM_CAP_KVMCLOCK_CTRL:
	case KVM_CAP_READONLY_MEM:
#ifdef CONFIG_KVM_DEVICE_ASSIGNMENT
	case KVM_CAP_ASSIGN_DEV_IRQ:
	case KVM_CAP_PCI_2_3:
#endif
		r = 1;
		break;
	case KVM_CAP_COALESCED_MMIO:
		r = KVM_COALESCED_MMIO_PAGE_OFFSET;
		break;
	case KVM_CAP_VAPIC:
		r = !kvm_x86_ops->cpu_has_accelerated_tpr();
		break;
	case KVM_CAP_NR_VCPUS:
		r = KVM_SOFT_MAX_VCPUS;
		break;
	case KVM_CAP_MAX_VCPUS:
		r = KVM_MAX_VCPUS;
		break;
	case KVM_CAP_NR_MEMSLOTS:
		r = KVM_USER_MEM_SLOTS;
		break;
	case KVM_CAP_PV_MMU:	/* obsolete */
		r = 0;
		break;
#ifdef CONFIG_KVM_DEVICE_ASSIGNMENT
	case KVM_CAP_IOMMU:
		r = iommu_present(&pci_bus_type);
		break;
#endif
	case KVM_CAP_MCE:
		r = KVM_MAX_MCE_BANKS;
		break;
	case KVM_CAP_XCRS:
		r = cpu_has_xsave;
		break;
	case KVM_CAP_TSC_CONTROL:
		r = kvm_has_tsc_control;
		break;
	case KVM_CAP_TSC_DEADLINE_TIMER:
		r = boot_cpu_has(X86_FEATURE_TSC_DEADLINE_TIMER);
		break;
	default:
		r = 0;
		break;
	}
