switch (cap->cap) {
	case KVM_CAP_PPC_OSI:
		r = 0;
		vcpu->arch.osi_enabled = true;
		break;
	case KVM_CAP_PPC_PAPR:
		r = 0;
		vcpu->arch.papr_enabled = true;
		break;
	case KVM_CAP_PPC_EPR:
		r = 0;
		if (cap->args[0])
			vcpu->arch.epr_flags |= KVMPPC_EPR_USER;
		else
			vcpu->arch.epr_flags &= ~KVMPPC_EPR_USER;
		break;
#ifdef CONFIG_BOOKE
	case KVM_CAP_PPC_BOOKE_WATCHDOG:
		r = 0;
		vcpu->arch.watchdog_enabled = true;
		break;
#endif
#if defined(CONFIG_KVM_E500V2) || defined(CONFIG_KVM_E500MC)
	case KVM_CAP_SW_TLB: {
		struct kvm_config_tlb cfg;
		void __user *user_ptr = (void __user *)(uintptr_t)cap->args[0];

		r = -EFAULT;
		if (copy_from_user(&cfg, user_ptr, sizeof(cfg)))
			break;

		r = kvm_vcpu_ioctl_config_tlb(vcpu, &cfg);
		break;
	}
#endif
#ifdef CONFIG_KVM_MPIC
	case KVM_CAP_IRQ_MPIC: {
		struct file *filp;
		struct kvm_device *dev;

		r = -EBADF;
		filp = fget(cap->args[0]);
		if (!filp)
			break;

		r = -EPERM;
		dev = kvm_device_from_filp(filp);
		if (dev)
			r = kvmppc_mpic_connect_vcpu(dev, vcpu, cap->args[1]);

		fput(filp);
		break;
	}
#endif
#ifdef CONFIG_KVM_XICS
	case KVM_CAP_IRQ_XICS: {
		struct file *filp;
		struct kvm_device *dev;

		r = -EBADF;
		filp = fget(cap->args[0]);
		if (!filp)
			break;

		r = -EPERM;
		dev = kvm_device_from_filp(filp);
		if (dev)
			r = kvmppc_xics_connect_vcpu(dev, vcpu, cap->args[1]);

		fput(filp);
		break;
	}
#endif /* CONFIG_KVM_XICS */
	default:
		r = -EINVAL;
		break;
	}
