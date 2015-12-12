switch (ioctl) {
	case KVM_PPC_GET_PVINFO: {
		struct kvm_ppc_pvinfo pvinfo;
		memset(&pvinfo, 0, sizeof(pvinfo));
		r = kvm_vm_ioctl_get_pvinfo(&pvinfo);
		if (copy_to_user(argp, &pvinfo, sizeof(pvinfo))) {
			r = -EFAULT;
			goto out;
		}

		break;
	}
#ifdef CONFIG_KVM_BOOK3S_64_HV
	case KVM_CREATE_SPAPR_TCE: {
		struct kvm_create_spapr_tce create_tce;
		struct kvm *kvm = filp->private_data;

		r = -EFAULT;
		if (copy_from_user(&create_tce, argp, sizeof(create_tce)))
			goto out;
		r = kvm_vm_ioctl_create_spapr_tce(kvm, &create_tce);
		goto out;
	}

	case KVM_ALLOCATE_RMA: {
		struct kvm *kvm = filp->private_data;
		struct kvm_allocate_rma rma;

		r = kvm_vm_ioctl_allocate_rma(kvm, &rma);
		if (r >= 0 && copy_to_user(argp, &rma, sizeof(rma)))
			r = -EFAULT;
		break;
	}
#endif /* CONFIG_KVM_BOOK3S_64_HV */

	default:
		r = -ENOTTY;
	}
