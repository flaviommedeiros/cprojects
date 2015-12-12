switch (type) {
	case KVM_VGIC_V2_ADDR_TYPE_DIST:
		type_needed = KVM_DEV_TYPE_ARM_VGIC_V2;
		addr_ptr = &vgic->vgic_dist_base;
		block_size = KVM_VGIC_V2_DIST_SIZE;
		alignment = SZ_4K;
		break;
	case KVM_VGIC_V2_ADDR_TYPE_CPU:
		type_needed = KVM_DEV_TYPE_ARM_VGIC_V2;
		addr_ptr = &vgic->vgic_cpu_base;
		block_size = KVM_VGIC_V2_CPU_SIZE;
		alignment = SZ_4K;
		break;
#ifdef CONFIG_KVM_ARM_VGIC_V3
	case KVM_VGIC_V3_ADDR_TYPE_DIST:
		type_needed = KVM_DEV_TYPE_ARM_VGIC_V3;
		addr_ptr = &vgic->vgic_dist_base;
		block_size = KVM_VGIC_V3_DIST_SIZE;
		alignment = SZ_64K;
		break;
	case KVM_VGIC_V3_ADDR_TYPE_REDIST:
		type_needed = KVM_DEV_TYPE_ARM_VGIC_V3;
		addr_ptr = &vgic->vgic_redist_base;
		block_size = KVM_VGIC_V3_REDIST_SIZE;
		alignment = SZ_64K;
		break;
#endif
	default:
		r = -ENODEV;
		goto out;
	}
