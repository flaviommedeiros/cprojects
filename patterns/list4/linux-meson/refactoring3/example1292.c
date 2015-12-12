switch (ioctl) {
	case KVM_ASSIGN_PCI_DEVICE: {
		struct kvm_assigned_pci_dev assigned_dev;

		r = -EFAULT;
		if (copy_from_user(&assigned_dev, argp, sizeof assigned_dev))
			goto out;
		r = kvm_vm_ioctl_assign_device(kvm, &assigned_dev);
		if (r)
			goto out;
		break;
	}
	case KVM_ASSIGN_IRQ: {
		r = -EOPNOTSUPP;
		break;
	}
	case KVM_ASSIGN_DEV_IRQ: {
		struct kvm_assigned_irq assigned_irq;

		r = -EFAULT;
		if (copy_from_user(&assigned_irq, argp, sizeof assigned_irq))
			goto out;
		r = kvm_vm_ioctl_assign_irq(kvm, &assigned_irq);
		if (r)
			goto out;
		break;
	}
	case KVM_DEASSIGN_DEV_IRQ: {
		struct kvm_assigned_irq assigned_irq;

		r = -EFAULT;
		if (copy_from_user(&assigned_irq, argp, sizeof assigned_irq))
			goto out;
		r = kvm_vm_ioctl_deassign_dev_irq(kvm, &assigned_irq);
		if (r)
			goto out;
		break;
	}
	case KVM_DEASSIGN_PCI_DEVICE: {
		struct kvm_assigned_pci_dev assigned_dev;

		r = -EFAULT;
		if (copy_from_user(&assigned_dev, argp, sizeof assigned_dev))
			goto out;
		r = kvm_vm_ioctl_deassign_device(kvm, &assigned_dev);
		if (r)
			goto out;
		break;
	}
#ifdef __KVM_HAVE_MSIX
	case KVM_ASSIGN_SET_MSIX_NR: {
		struct kvm_assigned_msix_nr entry_nr;
		r = -EFAULT;
		if (copy_from_user(&entry_nr, argp, sizeof entry_nr))
			goto out;
		r = kvm_vm_ioctl_set_msix_nr(kvm, &entry_nr);
		if (r)
			goto out;
		break;
	}
	case KVM_ASSIGN_SET_MSIX_ENTRY: {
		struct kvm_assigned_msix_entry entry;
		r = -EFAULT;
		if (copy_from_user(&entry, argp, sizeof entry))
			goto out;
		r = kvm_vm_ioctl_set_msix_entry(kvm, &entry);
		if (r)
			goto out;
		break;
	}
#endif
	case KVM_ASSIGN_SET_INTX_MASK: {
		struct kvm_assigned_pci_dev assigned_dev;

		r = -EFAULT;
		if (copy_from_user(&assigned_dev, argp, sizeof assigned_dev))
			goto out;
		r = kvm_vm_ioctl_set_pci_irq_mask(kvm, &assigned_dev);
		break;
	}
	default:
		r = -ENOTTY;
		break;
	}
