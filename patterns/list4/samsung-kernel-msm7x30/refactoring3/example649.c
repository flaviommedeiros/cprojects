switch (ext) {
#ifdef CONFIG_BOOKE
	case KVM_CAP_PPC_BOOKE_SREGS:
#else
	case KVM_CAP_PPC_SEGSTATE:
	case KVM_CAP_PPC_HIOR:
	case KVM_CAP_PPC_PAPR:
#endif
	case KVM_CAP_PPC_UNSET_IRQ:
	case KVM_CAP_PPC_IRQ_LEVEL:
	case KVM_CAP_ENABLE_CAP:
	case KVM_CAP_ONE_REG:
		r = 1;
		break;
#ifndef CONFIG_KVM_BOOK3S_64_HV
	case KVM_CAP_PPC_PAIRED_SINGLES:
	case KVM_CAP_PPC_OSI:
	case KVM_CAP_PPC_GET_PVINFO:
#ifdef CONFIG_KVM_E500
	case KVM_CAP_SW_TLB:
#endif
		r = 1;
		break;
	case KVM_CAP_COALESCED_MMIO:
		r = KVM_COALESCED_MMIO_PAGE_OFFSET;
		break;
#endif
#ifdef CONFIG_KVM_BOOK3S_64_HV
	case KVM_CAP_SPAPR_TCE:
		r = 1;
		break;
	case KVM_CAP_PPC_SMT:
		r = threads_per_core;
		break;
	case KVM_CAP_PPC_RMA:
		r = 1;
		/* PPC970 requires an RMA */
		if (cpu_has_feature(CPU_FTR_ARCH_201))
			r = 2;
		break;
	case KVM_CAP_SYNC_MMU:
		r = cpu_has_feature(CPU_FTR_ARCH_206) ? 1 : 0;
		break;
#endif
	case KVM_CAP_NR_VCPUS:
		/*
		 * Recommending a number of CPUs is somewhat arbitrary; we
		 * return the number of present CPUs for -HV (since a host
		 * will have secondary threads "offline"), and for other KVM
		 * implementations just count online CPUs.
		 */
#ifdef CONFIG_KVM_BOOK3S_64_HV
		r = num_present_cpus();
#else
		r = num_online_cpus();
#endif
		break;
	case KVM_CAP_MAX_VCPUS:
		r = KVM_MAX_VCPUS;
		break;
	default:
		r = 0;
		break;
	}
