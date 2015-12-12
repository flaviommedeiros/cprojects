switch (ioctl) {
	case KVM_S390_IRQ: {
		struct kvm_s390_irq s390irq;

		r = -EFAULT;
		if (copy_from_user(&s390irq, argp, sizeof(s390irq)))
			break;
		r = kvm_s390_inject_vcpu(vcpu, &s390irq);
		break;
	}
	case KVM_S390_INTERRUPT: {
		struct kvm_s390_interrupt s390int;
		struct kvm_s390_irq s390irq;

		r = -EFAULT;
		if (copy_from_user(&s390int, argp, sizeof(s390int)))
			break;
		if (s390int_to_s390irq(&s390int, &s390irq))
			return -EINVAL;
		r = kvm_s390_inject_vcpu(vcpu, &s390irq);
		break;
	}
	case KVM_S390_STORE_STATUS:
		idx = srcu_read_lock(&vcpu->kvm->srcu);
		r = kvm_s390_vcpu_store_status(vcpu, arg);
		srcu_read_unlock(&vcpu->kvm->srcu, idx);
		break;
	case KVM_S390_SET_INITIAL_PSW: {
		psw_t psw;

		r = -EFAULT;
		if (copy_from_user(&psw, argp, sizeof(psw)))
			break;
		r = kvm_arch_vcpu_ioctl_set_initial_psw(vcpu, psw);
		break;
	}
	case KVM_S390_INITIAL_RESET:
		r = kvm_arch_vcpu_ioctl_initial_reset(vcpu);
		break;
	case KVM_SET_ONE_REG:
	case KVM_GET_ONE_REG: {
		struct kvm_one_reg reg;
		r = -EFAULT;
		if (copy_from_user(&reg, argp, sizeof(reg)))
			break;
		if (ioctl == KVM_SET_ONE_REG)
			r = kvm_arch_vcpu_ioctl_set_one_reg(vcpu, &reg);
		else
			r = kvm_arch_vcpu_ioctl_get_one_reg(vcpu, &reg);
		break;
	}
#ifdef CONFIG_KVM_S390_UCONTROL
	case KVM_S390_UCAS_MAP: {
		struct kvm_s390_ucas_mapping ucasmap;

		if (copy_from_user(&ucasmap, argp, sizeof(ucasmap))) {
			r = -EFAULT;
			break;
		}

		if (!kvm_is_ucontrol(vcpu->kvm)) {
			r = -EINVAL;
			break;
		}

		r = gmap_map_segment(vcpu->arch.gmap, ucasmap.user_addr,
				     ucasmap.vcpu_addr, ucasmap.length);
		break;
	}
	case KVM_S390_UCAS_UNMAP: {
		struct kvm_s390_ucas_mapping ucasmap;

		if (copy_from_user(&ucasmap, argp, sizeof(ucasmap))) {
			r = -EFAULT;
			break;
		}

		if (!kvm_is_ucontrol(vcpu->kvm)) {
			r = -EINVAL;
			break;
		}

		r = gmap_unmap_segment(vcpu->arch.gmap, ucasmap.vcpu_addr,
			ucasmap.length);
		break;
	}
#endif
	case KVM_S390_VCPU_FAULT: {
		r = gmap_fault(vcpu->arch.gmap, arg, 0);
		break;
	}
	case KVM_ENABLE_CAP:
	{
		struct kvm_enable_cap cap;
		r = -EFAULT;
		if (copy_from_user(&cap, argp, sizeof(cap)))
			break;
		r = kvm_vcpu_ioctl_enable_cap(vcpu, &cap);
		break;
	}
	case KVM_S390_MEM_OP: {
		struct kvm_s390_mem_op mem_op;

		if (copy_from_user(&mem_op, argp, sizeof(mem_op)) == 0)
			r = kvm_s390_guest_mem_op(vcpu, &mem_op);
		else
			r = -EFAULT;
		break;
	}
	case KVM_S390_SET_IRQ_STATE: {
		struct kvm_s390_irq_state irq_state;

		r = -EFAULT;
		if (copy_from_user(&irq_state, argp, sizeof(irq_state)))
			break;
		if (irq_state.len > VCPU_IRQS_MAX_BUF ||
		    irq_state.len == 0 ||
		    irq_state.len % sizeof(struct kvm_s390_irq) > 0) {
			r = -EINVAL;
			break;
		}
		r = kvm_s390_set_irq_state(vcpu,
					   (void __user *) irq_state.buf,
					   irq_state.len);
		break;
	}
	case KVM_S390_GET_IRQ_STATE: {
		struct kvm_s390_irq_state irq_state;

		r = -EFAULT;
		if (copy_from_user(&irq_state, argp, sizeof(irq_state)))
			break;
		if (irq_state.len == 0) {
			r = -EINVAL;
			break;
		}
		r = kvm_s390_get_irq_state(vcpu,
					   (__u8 __user *)  irq_state.buf,
					   irq_state.len);
		break;
	}
	default:
		r = -ENOTTY;
	}
