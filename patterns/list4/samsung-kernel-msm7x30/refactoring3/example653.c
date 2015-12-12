switch (ioctl) {
	case KVM_INTERRUPT: {
		struct kvm_interrupt irq;
		r = -EFAULT;
		if (copy_from_user(&irq, argp, sizeof(irq)))
			goto out;
		r = kvm_vcpu_ioctl_interrupt(vcpu, &irq);
		goto out;
	}

	case KVM_ENABLE_CAP:
	{
		struct kvm_enable_cap cap;
		r = -EFAULT;
		if (copy_from_user(&cap, argp, sizeof(cap)))
			goto out;
		r = kvm_vcpu_ioctl_enable_cap(vcpu, &cap);
		break;
	}

	case KVM_SET_ONE_REG:
	case KVM_GET_ONE_REG:
	{
		struct kvm_one_reg reg;
		r = -EFAULT;
		if (copy_from_user(&reg, argp, sizeof(reg)))
			goto out;
		if (ioctl == KVM_SET_ONE_REG)
			r = kvm_vcpu_ioctl_set_one_reg(vcpu, &reg);
		else
			r = kvm_vcpu_ioctl_get_one_reg(vcpu, &reg);
		break;
	}

#ifdef CONFIG_KVM_E500
	case KVM_DIRTY_TLB: {
		struct kvm_dirty_tlb dirty;
		r = -EFAULT;
		if (copy_from_user(&dirty, argp, sizeof(dirty)))
			goto out;
		r = kvm_vcpu_ioctl_dirty_tlb(vcpu, &dirty);
		break;
	}
#endif

	default:
		r = -EINVAL;
	}
