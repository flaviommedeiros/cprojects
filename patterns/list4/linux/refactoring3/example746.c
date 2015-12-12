switch (type) {
	case KVM_DEV_TYPE_ARM_VGIC_V2:
		vgic_v2_init_emulation(kvm);
		break;
#ifdef CONFIG_KVM_ARM_VGIC_V3
	case KVM_DEV_TYPE_ARM_VGIC_V3:
		vgic_v3_init_emulation(kvm);
		break;
#endif
	default:
		return -ENODEV;
	}
