switch (cd->type) {
#ifdef CONFIG_KVM_MPIC
	case KVM_DEV_TYPE_FSL_MPIC_20:
	case KVM_DEV_TYPE_FSL_MPIC_42:
		ops = &kvm_mpic_ops;
		break;
#endif
#ifdef CONFIG_KVM_XICS
	case KVM_DEV_TYPE_XICS:
		ops = &kvm_xics_ops;
		break;
#endif
	default:
		return -ENODEV;
	}
