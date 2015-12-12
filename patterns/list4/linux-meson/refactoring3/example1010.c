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
#ifdef CONFIG_PPC_BOOK3S_64
	case KVM_CREATE_SPAPR_TCE: {
		struct kvm_create_spapr_tce create_tce;

		r = -EFAULT;
		if (copy_from_user(&create_tce, argp, sizeof(create_tce)))
			goto out;
		r = kvm_vm_ioctl_create_spapr_tce(kvm, &create_tce);
		goto out;
	}
#endif /* CONFIG_PPC_BOOK3S_64 */

#ifdef CONFIG_KVM_BOOK3S_64_HV
	case KVM_ALLOCATE_RMA: {
		struct kvm_allocate_rma rma;
		struct kvm *kvm = filp->private_data;

		r = kvm_vm_ioctl_allocate_rma(kvm, &rma);
		if (r >= 0 && copy_to_user(argp, &rma, sizeof(rma)))
			r = -EFAULT;
		break;
	}

	case KVM_PPC_ALLOCATE_HTAB: {
		u32 htab_order;

		r = -EFAULT;
		if (get_user(htab_order, (u32 __user *)argp))
			break;
		r = kvmppc_alloc_reset_hpt(kvm, &htab_order);
		if (r)
			break;
		r = -EFAULT;
		if (put_user(htab_order, (u32 __user *)argp))
			break;
		r = 0;
		break;
	}

	case KVM_PPC_GET_HTAB_FD: {
		struct kvm_get_htab_fd ghf;

		r = -EFAULT;
		if (copy_from_user(&ghf, argp, sizeof(ghf)))
			break;
		r = kvm_vm_ioctl_get_htab_fd(kvm, &ghf);
		break;
	}
#endif /* CONFIG_KVM_BOOK3S_64_HV */

#ifdef CONFIG_PPC_BOOK3S_64
	case KVM_PPC_GET_SMMU_INFO: {
		struct kvm_ppc_smmu_info info;

		memset(&info, 0, sizeof(info));
		r = kvm_vm_ioctl_get_smmu_info(kvm, &info);
		if (r >= 0 && copy_to_user(argp, &info, sizeof(info)))
			r = -EFAULT;
		break;
	}
	case KVM_PPC_RTAS_DEFINE_TOKEN: {
		struct kvm *kvm = filp->private_data;

		r = kvm_vm_ioctl_rtas_define_token(kvm, argp);
		break;
	}
#endif /* CONFIG_PPC_BOOK3S_64 */
	default:
		r = -ENOTTY;
	}
