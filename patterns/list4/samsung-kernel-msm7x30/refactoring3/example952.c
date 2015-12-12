switch (ioctl) {
	case KVM_CREATE_VCPU:
		r = kvm_vm_ioctl_create_vcpu(kvm, arg);
		if (r < 0)
			goto out;
		break;
	case KVM_SET_USER_MEMORY_REGION: {
		struct kvm_userspace_memory_region kvm_userspace_mem;

		r = -EFAULT;
		if (copy_from_user(&kvm_userspace_mem, argp,
						sizeof kvm_userspace_mem))
			goto out;

		r = kvm_vm_ioctl_set_memory_region(kvm, &kvm_userspace_mem, 1);
		if (r)
			goto out;
		break;
	}
	case KVM_GET_DIRTY_LOG: {
		struct kvm_dirty_log log;

		r = -EFAULT;
		if (copy_from_user(&log, argp, sizeof log))
			goto out;
		r = kvm_vm_ioctl_get_dirty_log(kvm, &log);
		if (r)
			goto out;
		break;
	}
#ifdef KVM_COALESCED_MMIO_PAGE_OFFSET
	case KVM_REGISTER_COALESCED_MMIO: {
		struct kvm_coalesced_mmio_zone zone;
		r = -EFAULT;
		if (copy_from_user(&zone, argp, sizeof zone))
			goto out;
		r = kvm_vm_ioctl_register_coalesced_mmio(kvm, &zone);
		if (r)
			goto out;
		r = 0;
		break;
	}
	case KVM_UNREGISTER_COALESCED_MMIO: {
		struct kvm_coalesced_mmio_zone zone;
		r = -EFAULT;
		if (copy_from_user(&zone, argp, sizeof zone))
			goto out;
		r = kvm_vm_ioctl_unregister_coalesced_mmio(kvm, &zone);
		if (r)
			goto out;
		r = 0;
		break;
	}
#endif
	case KVM_IRQFD: {
		struct kvm_irqfd data;

		r = -EFAULT;
		if (copy_from_user(&data, argp, sizeof data))
			goto out;
		r = kvm_irqfd(kvm, data.fd, data.gsi, data.flags);
		break;
	}
	case KVM_IOEVENTFD: {
		struct kvm_ioeventfd data;

		r = -EFAULT;
		if (copy_from_user(&data, argp, sizeof data))
			goto out;
		r = kvm_ioeventfd(kvm, &data);
		break;
	}
#ifdef CONFIG_KVM_APIC_ARCHITECTURE
	case KVM_SET_BOOT_CPU_ID:
		r = 0;
		mutex_lock(&kvm->lock);
		if (atomic_read(&kvm->online_vcpus) != 0)
			r = -EBUSY;
		else
			kvm->bsp_vcpu_id = arg;
		mutex_unlock(&kvm->lock);
		break;
#endif
	default:
		r = kvm_arch_vm_ioctl(filp, ioctl, arg);
		if (r == -ENOTTY)
			r = kvm_vm_ioctl_assigned_device(kvm, ioctl, arg);
	}
